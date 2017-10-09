#include <mraa/aio.h>
#include <stdlib.h>

typedef struct {
	mraa_aio_context rotary;
	int reading;
	float temperature;
	float slope, intercept;
} KNOB;

KNOB* knob_init(int aio_pin, float upper, float lower);
float knob_read(KNOB* knob);
void knob_off(KNOB *knob);

