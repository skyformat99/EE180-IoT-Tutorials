#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <mraa/aio.h>

sig_atomic_t volatile run_flag = 1;

void do_when_interrupted(int sig)
{
	if (sig == SIGINT)
		run_flag = 0;
}

int main()
{
	unit16_t value;

	mraa_aio_context rotary;

	rotary = mraa_aio_init(0);

	signal(SIGINT, do_when_interrupted);

	while(run_flag) {
		value = mraa_aio_read(rotary);
		printf("%d\n", value);
		sleep(1);
	}

	mraa_aio_close(rotary);

	return 0;
}