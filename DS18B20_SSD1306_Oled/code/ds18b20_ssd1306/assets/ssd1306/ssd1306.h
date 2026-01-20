#ifndef SSD1306_PROTOTYPES_H
#define SSD1306_PROTOTYPES_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
#include "../characters/charset.h"
//------------------------------------------------------------------------------
#define I2C_ADDRESS 			0x3C
// SSD1306 Commands
#define DISPLAY_OFF 			0xAE
#define DISPLAY_ON  			0xAF
#define SET_CONTRAST 			0x81
#define DISPLAY_RAM 			0xA4
#define MEMORY_MODE 			0x20
#define SET_PAGE_ADDR 		    0xB0
#define SET_COLUMN_ADDR 	    0x21
#define SCREEN_WIDTH 			128
#define SCREEN_HEIGHT			64
//------------------------------------------------------------------------------
void ssd1306_init(void);
void ssd1306_command(uint8_t command);
void ssd1306_data(uint8_t data_);
void ssd1306_print(uint8_t row, uint8_t col, uint8_t text[]);
void ssd1306_displayImage(uint16_t width, uint16_t height, const uint8_t *bitmap);
void writeChar(uint8_t row);
//------------------------------------------------------------------------------
#endif