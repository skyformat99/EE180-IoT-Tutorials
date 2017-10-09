#include "client.h"
#include "thermistor.h"
#include <signal.h>
#include <mraa.h>
#include <sys/time.h>

static volatile int run_flag = 1;

void do_when_interrupted()
{
	run_flag = 0;
}

int client_handle_connection(int client_socket_fd, THERMISTOR *thermistor)
{
	int n;
	char buffer[256];
	struct timeval tv;
	double sec_since_epoch;

	memset(buffer, 0, 256);
	sprintf(buffer, "time (epoch),temperature/C");

	n = write(client_socket_fd, buffer, strlen(buffer));
	if (n < 0) {
		return client_error("ERROR writing to socket");
	}

	memset(buffer, 0, 256);

	n = read(client_socket_fd, buffer, 255);
	if (n < 0) {
		return client_error("ERROR reading from socket");
	}

	printf("msg from server: %s\n", buffer);

	while (run_flag) {
		gettimeofday(&tv, NULL);
		sec_since_epoch = (double) tv.tv_sec + (double) tv.tv_usec/1000000.0;

		memset(buffer, 0, 256);
		sprintf(buffer, "%10.10f,%4.2f", sec_since_epoch, thermistor_read(thermistor));

		n = write(client_socket_fd, buffer, strlen(buffer));
		if (n < 0) {
			return client_error("ERROR writing to socket");
		}

		memset(buffer, 0, 256);

		n = read(client_socket_fd, buffer, 255);
		if (n < 0) {
			return client_error("ERROR reading from socket");
		}

		printf("msg from server: %s\n", buffer);
		usleep(500000);
	}
	close(client_socket_fd);
	return 1;
}

int main(int argc, char *argv[])
{
	THERMISTOR *thermistor;
	int client_socket_fd;

	signal(SIGINT, do_when_interrupted);

	mraa_init();

	thermistor = thermistor_init(0, 'C');
	client_socket_fd = client_init(argc, argv, 10);
	if (client_socket_fd < 0) {
		perror("ERROR connecting to server");
		return -1;
	}

	client_handle_connection(client_socket_fd, thermistor);

	return 0;
}
