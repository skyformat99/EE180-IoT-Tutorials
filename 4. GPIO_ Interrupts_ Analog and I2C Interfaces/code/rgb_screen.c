#include <mraa/i2c.h>

#define RGB_ADDRESS (0xc4 >> 1)
#define REG_MODE1 0x00
#define REG_MODE2 0x01
#define REG_OUTPUT 0x08

#define REG_RED 0x04
#define REG_GREEN 0x03
#define REG_BLUE 0x02

void rgb_command(mraa_i2c_context rgb_i2c, unit8_t addr, unit8_t dta)
{
	unit8_t to_send[2] = {addr, dta};
	mraa_i2c_write(rgb_i2c, to_send, 2);
}

void set_RGB_color(mraa_i2c_context rgb_i2c, unit8_t r, unit8_t g, unit8_t b)
{
	rgb_command(rgb_i2c, REG_RED, r);
	rgb_command(rgb_i2c, REG_GREEN, g);
	rgb_command(rgb_i2c, REG_BLUE, b);
}

int main()
{
	mraa_i2c_context rgb_i2c;

	mraa_init();

	rgb_i2c = mraa_i2c_init(0);

	mraa_i2c_address(rgb_i2c, RGB_ADDRESS);

	rgb_command(rgb_i2c, REG_MODE1, 0);
	rgb_command(rgb_i2c, REG_MODE2, 0x20);
	rgb_command(rgb_i2c, REG_OUTPUT, 0xFF);

	set_RGB_color(rgb_i2c, 0, 0, 255);
}
