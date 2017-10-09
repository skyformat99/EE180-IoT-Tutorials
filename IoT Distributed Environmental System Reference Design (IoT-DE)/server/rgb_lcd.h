#ifndef __RGB_LCD_H__
#define __RGB_LCD_H__

#include <stdint.h>
#include <mraa/i2c.h>
#include <string.h>
#include <unistd.h>

// Device I2C Arress
#define LCD_ADDRESS     (0x7c>>1)
#define RGB_ADDRESS     (0xc4>>1)

// color define 
#define WHITE           0
#define RED             1
#define GREEN           2
#define BLUE            3

#define REG_RED         0x04        // pwm2
#define REG_GREEN       0x03        // pwm1
#define REG_BLUE        0x02        // pwm0

#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_OUTPUT      0x08

// commands
#define LCD_CLEARDISPLAY	0x01
#define LCD_RETURNHOME		0x02
#define LCD_ENTRYMODESET	0x04
#define LCD_DISPLAYCONTROL	0x08
#define LCD_CURSORSHIFT		0x10
#define LCD_FUNCTIONSET		0x20
#define LCD_SETCGRAMADDR	0x40
#define LCD_SETDDRAMADDR	0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT			0x00
#define LCD_ENTRYLEFT			0x02
#define LCD_ENTRYSHIFTINCREMENT	0x01
#define LCD_ENTRYSHIFTDECREMENT	0x00

// flags for display on/off control
#define LCD_DISPLAYON	0x04
#define LCD_DISPLAYOFF	0x00
#define LCD_CURSORON	0x02
#define LCD_CURSOROFF	0x00
#define LCD_BLINKON		0x01
#define LCD_BLINKOFF	0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE	0x08
#define LCD_CURSORMOVE	0x00
#define LCD_MOVERIGHT	0x04
#define LCD_MOVELEFT	0x00

// flags for function set
#define LCD_8BITMODE	0x10
#define LCD_4BITMODE	0x00
#define LCD_2LINE		0x08
#define LCD_1LINE		0x00
#define LCD_5x10DOTS	0x04
#define LCD_5x8DOTS		0x00

typedef struct {
	mraa_i2c_context lcd_i2c;
	mraa_i2c_context rgb_i2c;

	uint8_t display_function;
	uint8_t display_control;	
	uint8_t display_mode;
	
	uint8_t cursor_pos;
} RGB_LCD;

RGB_LCD* rgb_lcd_init();

void rgb_lcd_LCD_command(RGB_LCD *rgb_lcd, uint8_t value);
void rgb_lcd_RGB_command(RGB_LCD *rgb_lcd, uint8_t addr, uint8_t dta);

void rgb_lcd_setCursor(RGB_LCD *rgb_lcd, uint8_t col, uint8_t row);
void rgb_lcd_clear(RGB_LCD *rgb_lcd);
void rgb_lcd_home(RGB_LCD *rgb_lcd);

void rgb_lcd_noDisplay(RGB_LCD *rgb_lcd);
void rgb_lcd_display(RGB_LCD *rgb_lcd);

void rgb_lcd_setRGB(RGB_LCD *rgb_lcd, uint8_t r, uint8_t g, uint8_t b);

void rgb_lcd_write_char(RGB_LCD *rgb_lcd, uint8_t value);
void rgb_lcd_print(RGB_LCD *rgb_lcd, char s[]);

#endif
