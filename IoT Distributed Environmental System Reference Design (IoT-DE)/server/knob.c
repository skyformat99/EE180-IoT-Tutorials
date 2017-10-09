#include "knob.h"

KNOB* knob_init(int aio_pin, float upper, float lower)
{
	KNOB* knob;
	
	knob = malloc(sizeof(KNOB));
	
	knob->rotary = mraa_aio_init(aio_pin);
	knob->temperature = 69.0;
	knob->slope = (upper-lower)/1023.0;
	knob->intercept = lower;

	return knob;	
}

float knob_read(KNOB* knob)
{
	knob->reading = mraa_aio_read(knob->rotary);
	knob->temperature = ( (float)knob->reading ) * knob->slope + knob->intercept;
	return knob->temperature;
}

void knob_off(KNOB *knob)
{
	mraa_aio_close(knob->rotary);
}
