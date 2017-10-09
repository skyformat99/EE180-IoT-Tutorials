/*
   rgb_lcd.cpp
   2013 Copyright (c) Seeed Technology Inc.  All right reserved.
Author:Loovee
2013-9-18
add rgb backlight fucnction @ 2013-10-15

The MIT License (MIT)
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.1  USA
*/

#include "rgb_lcd.h"

RGB_LCD* rgb_lcd_init()
{
	RGB_LCD *rgb_lcd;
	rgb_lcd = malloc(sizeof(RGB_LCD));

	// initialize all the params in the struct
	rgb_lcd->lcd_i2c = mraa_i2c_init(6);
	rgb_lcd->rgb_i2c = mraa_i2c_init(6);
	rgb_lcd->display_function = 0;
	rgb_lcd->display_control = 0;
	rgb_lcd->display_mode = 0;
	rgb_lcd->cursor_pos = 0;

	// set up the i2c busses
	mraa_i2c_address(rgb_lcd->lcd_i2c, LCD_ADDRESS);
	mraa_i2c_address(rgb_lcd->rgb_i2c, RGB_ADDRESS);

	// set up the lcd screen
	rgb_lcd->display_function |= LCD_2LINE;

	usleep(50000);
	rgb_lcd_LCD_command(rgb_lcd, LCD_FUNCTIONSET | rgb_lcd->display_function);

	usleep(4500);	
	rgb_lcd_LCD_command(rgb_lcd, LCD_FUNCTIONSET | rgb_lcd->display_function);

	usleep(150);	
	rgb_lcd_LCD_command(rgb_lcd, LCD_FUNCTIONSET | rgb_lcd->display_function);

	rgb_lcd_LCD_command(rgb_lcd, LCD_FUNCTIONSET | rgb_lcd->display_function);

	// display a blinking cursor
	rgb_lcd->display_control = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKON;
	rgb_lcd_display(rgb_lcd);

	// clear the screen
	rgb_lcd_clear(rgb_lcd);

	rgb_lcd->display_mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	rgb_lcd_LCD_command(rgb_lcd, LCD_ENTRYMODESET | rgb_lcd->display_mode);

	// set up the rgb backlight
	rgb_lcd_RGB_command(rgb_lcd, REG_MODE1, 0);
	rgb_lcd_RGB_command(rgb_lcd, REG_OUTPUT, 0xFF);
	rgb_lcd_RGB_command(rgb_lcd, REG_MODE2, 0x20);

	rgb_lcd_setRGB(rgb_lcd, 0, 0, 0);

	return rgb_lcd;
}

void rgb_lcd_LCD_command(RGB_LCD *rgb_lcd, uint8_t value){
	uint8_t dta[2] = {0x80, value};
	mraa_i2c_write(rgb_lcd->lcd_i2c, dta, 2);
}

void rgb_lcd_RGB_command(RGB_LCD *rgb_lcd, uint8_t addr, uint8_t dta){
	uint8_t to_send[2] = {addr, dta};
	mraa_i2c_write(rgb_lcd->rgb_i2c, to_send, 2); 
}

void rgb_lcd_setCursor(RGB_LCD *rgb_lcd, uint8_t col, uint8_t row){
	col = (row == 0 ? col|0x80 : col|0xc0);
	uint8_t dta[2] = {0x80, col};
	mraa_i2c_write(rgb_lcd->lcd_i2c, dta, 2);
	rgb_lcd->cursor_pos = row*2 + col;
}

void rgb_lcd_clear(RGB_LCD *rgb_lcd){
	rgb_lcd_LCD_command(rgb_lcd, LCD_CLEARDISPLAY);
	usleep(2000);
	rgb_lcd->cursor_pos = 0;
}

void rgb_lcd_home(RGB_LCD *rgb_lcd){
	rgb_lcd_setCursor(rgb_lcd, 0, 0);
	usleep(2000);
	rgb_lcd->cursor_pos = 0;
}

void rgb_lcd_noDisplay(RGB_LCD *rgb_lcd){
	rgb_lcd->display_control &= ~LCD_DISPLAYON;
	rgb_lcd_LCD_command(rgb_lcd, LCD_DISPLAYCONTROL | rgb_lcd->display_control);
}

void rgb_lcd_display(RGB_LCD *rgb_lcd){
	rgb_lcd->display_control |= LCD_DISPLAYON;
	rgb_lcd_LCD_command(rgb_lcd, LCD_DISPLAYCONTROL | rgb_lcd->display_control);
}

void rgb_lcd_setRGB(RGB_LCD *rgb_lcd, uint8_t r, uint8_t g, uint8_t b){
	rgb_lcd_RGB_command(rgb_lcd, REG_RED, r);
	rgb_lcd_RGB_command(rgb_lcd, REG_GREEN, g);
	rgb_lcd_RGB_command(rgb_lcd, REG_BLUE, b);
}

void rgb_lcd_write_char(RGB_LCD *rgb_lcd, uint8_t value){
	uint8_t dta[2] = {0x40, value};
	mraa_i2c_write(rgb_lcd->lcd_i2c, dta, 2);
}

void rgb_lcd_print(RGB_LCD *rgb_lcd, char s[]){
	int i, row, col;
	for(i=0; i<strlen(s); i++){
		row = (i/16)%2;
		col = i%16;
		rgb_lcd_setCursor(rgb_lcd, col, row);
		rgb_lcd_write_char(rgb_lcd, s[i]);
	}
}
