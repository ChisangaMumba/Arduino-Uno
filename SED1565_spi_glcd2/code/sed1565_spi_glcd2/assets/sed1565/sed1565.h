#ifndef SED1565_H
#define SED1565_H      
//------------------------------------------------------------------------------
#include "../spi/Soft_SPI.h"
//#include "image.h"
#include "ascii_chars.h"
//------------------------------------------------------------------------------
uint8_t CS1  = 10;         //Chip Select 1
uint8_t RS   = 8;    
uint8_t RST  = 7; 
//------------------------------------------------------------------------------
#define CLEAR       0x00
#define FILL        0xFF
#define pgLen       8
#define pgWidth     128
//-------------------------Glcd Pages addresses---------------------------------
const uint8_t page[8] = {0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7}; 
//------------------------------------------------------------------------------
void sed1565_init();
void sed1565_command(uint8_t command);
void sed1565_data(uint8_t data_);
void sed1565_fill(uint8_t fill);
void sed1565_page(uint8_t pg);
void sed1565_column(uint8_t column);
void sed1565_startline(uint8_t line);
void sed1565_setAddress(uint8_t page, uint8_t column);
void sed1565_printf(uint8_t pg, uint8_t col, uint8_t *text);
void sed1565_image(uint8_t *image);
void sed1565_reset(void);
void writeChar(uint8_t chr);
//------------------------------------------------------------------------------
#endif