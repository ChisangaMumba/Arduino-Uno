#ifndef SSD1308_H
#define SSD1308_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#include "charset.h"
//#include "image.h"
//------------------------------------------------------------------------------
uint8_t CS1 = 10;         //Chip Select 1
uint8_t DC  = 7;
uint8_t RST = 6;
//------------------------------------------------------------------------------
#define SSD1308_I2C_ADDRESS 			0x3C
// SSD1308 Commands
#define SSD1308_DISPLAY_OFF 			0xAE
#define SSD1308_DISPLAY_ON  			0xAF
#define SSD1308_SET_CONTRAST 			0x81
#define SSD1308_DISPLAY_RAM 			0xA4
#define SSD1308_MEMORY_MODE 			0x20
#define SSD1308_SET_PAGE_ADDR 		    0xB0
#define SSD1308_SET_COLUMN_ADDR 	    0x21
#define SCREEN_WIDTH 					128
#define SCREEN_HEIGHT					64
//------------------------------------------------------------------------------
void ssd1308_init(void);
void ssd1308_command(uint8_t command);
void ssd1308_data(uint8_t data);
void ssd1308_print(uint8_t row, uint8_t col, uint8_t text[]);
void ssd1308_displayImage(uint16_t width, uint16_t height, const uint8_t *bitmap);
void ssd1308_reset(void);
void writeChar(uint8_t row);
//------------------------------------------------------------------------------
#endif