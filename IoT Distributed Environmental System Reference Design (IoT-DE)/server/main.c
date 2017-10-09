#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <signal.h>
#include <pthread.h>

#include "server.h"
#include "rgb_lcd.h"
#include "knob.h"

#define PORTNO 5000

static volatile int run_flag = 1;

void do_when_interrupted()
{
	run_flag = 0;
	printf("\nThreads exiting. Please wait for cleanup operations to complete...\n");
}

void* manage_lcd(void *arg)
{
	RGB_LCD *rgb_lcd;
	KNOB *knob;
	char display_message[256];
	float prev_reading;

	mraa_init();

	rgb_lcd = rgb_lcd_init();
	knob = knob_init(3, 65.0, 79.0);

	prev_reading = 0;

	while(run_flag) {
		memset(display_message, 0, sizeof(display_message));	
		sprintf(display_message, "Temp Setting: %2.0f", knob_read(knob));
		// only update the LCD screen if there is a change to the temperature
		if ( (int) prev_reading != (int) knob->temperature )
		{
			printf("%s\n", display_message);
			rgb_lcd_clear(rgb_lcd);
			rgb_lcd_print(rgb_lcd, display_message);
			prev_reading = knob->temperature;
		}
		usleep(100000);
	}

	rgb_lcd_noDisplay(rgb_lcd);
	knob_off(knob);

	return NULL;
}

void* handle_client(void *arg)
{
	CONNECTION *client;
	int n, client_socket_fd;
	char buffer[256], tmp[256];
	FILE *fp;

	client = (CONNECTION *)arg;
	
	client_socket_fd = client->sockfd;

	memset(buffer, 0, 256);
	sprintf(buffer, "output_file_IP_%s_TIMESTAMP_%u.csv", client->ip_addr_str, (unsigned)time(NULL));
	printf("filename: %s", buffer);

	fp = fopen(buffer, "wb");

	while (run_flag) {
		// clear the buffer
		memset(buffer, 0, 256);

		// read what the client sent to the server and store it in "buffer"
		n = read(client_socket_fd, buffer, 255);	
		// an error has occurred
		if (n < 0) {
			server_error("ERROR reading from socket");
			return NULL;
		}
		// no data was sent, assume the connection was terminated
		if (n == 0) { 
			printf("%s has terminated the connection.\n", client->ip_addr_str);
			return NULL;
		}

		// print the message to console
		printf("%s says: %s\n", client->ip_addr_str, buffer);
		fprintf(fp, "%s\n", buffer);

		// send an acknowledgement back to the client saying that we received the message
		memset(tmp, 0, sizeof(tmp));
		sprintf(tmp, "%s sent the server: %s", client->ip_addr_str, buffer);
		n = write(client_socket_fd, tmp, strlen(tmp));
		if (n < 0) {
			server_error("ERROR writing to socket");
			return NULL;
		}
	}

	fclose(fp);
	close(client_socket_fd);
	return NULL;
}

void* manage_server(void *arg)
{
	CONNECTION *server;
	CONNECTION *client;
	int max_connections;
	int i;
	pthread_t tids[256];

	// this is the maximum number of connections that the server will accept before
	// turning down additional incoming clients. The server will continue to process
	// old connections until they are terminated
	max_connections = 10;

	// setup the server, second argument is how long to wait before realizing there
	// is no incoming client connection (IE: timeout, unit: SECONDS)
	server = (CONNECTION *) server_init(PORTNO, 10);
	if ((int) server == -1){
		run_flag = 0;
	}

	i = -1;

	while(i < max_connections && run_flag)
	{
		// wait for a client to connect
		client = (CONNECTION*) server_accept_connection(server->sockfd);
		// no incoming client connection was found
		if ((int) client == -1) {
			printf("Latest child process is waiting for an incoming client connection.\n");
		}
		// an incoming connection was found, service it by spawning a thread to handle the connection
		else {
			i++;
			pthread_create(&tids[i], NULL, handle_client, (void *)client);
		}
	}

	if (i >= max_connections) {
		printf("Max number of connections reached. No longer accepting connections. Continuing to service old connections.\n");
	}

	// wait for all the child threads to complete before exiting
	for(; i >= 0; i--) {
		pthread_join(tids[i], NULL);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t manage_lcd_tid, manage_server_tid;
	int rc;

	signal(SIGINT, do_when_interrupted);

	rc = pthread_create(&manage_lcd_tid, NULL, manage_lcd, NULL);
	if (rc != 0) {
		fprintf(stderr, "Failed to create manage_lcd thread. Exiting program.\n");
		exit(0);
	}

	rc = pthread_create(&manage_server_tid, NULL, manage_server, NULL);
	if (rc != 0) {
		fprintf(stderr, "Failed to create manage_server thread. Exiting program.\n");
		exit(0);
	}

	pthread_join(manage_lcd_tid, NULL);
	pthread_join(manage_server_tid, NULL);

	printf("\n...cleanup operations complete. Exiting main.\n");

	return 0;
}
