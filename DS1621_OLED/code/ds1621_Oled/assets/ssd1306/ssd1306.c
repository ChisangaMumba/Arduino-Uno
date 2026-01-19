#ifndef SSD1306_C
#define SSD1306_C
//------------------------------------------------------------------------------
#include "ssd1306.h"
#include <ctype.h>
//------------------------------------------------------------------------------
void ssd1306_init() 
{
	I2C_init(); 
	
	ssd1306_command(DISPLAY_OFF); // Display off
	ssd1306_command(0xD5); // Set display clock divide ratio
	ssd1306_command(0x80); // Suggested ratio
	ssd1306_command(0xA8); // Set multiplex ratio
	ssd1306_command(0x3F); // 1/64 duty
	ssd1306_command(0xD3); // Set display offset
	ssd1306_command(0x00); // No offset
	ssd1306_command(MEMORY_MODE); // Memory addressing mode
	ssd1306_command(0x00); // Horizontal addressing mode
	ssd1306_command(DISPLAY_RAM); // Output follows RAM content
	ssd1306_command(DISPLAY_ON); // Display on
}
//------------------------------------------------------------------------------
void ssd1306_command(uint8_t command) 
{
	I2C_start();
	
	I2C_write(I2C_ADDRESS << 1); // SSD1306 address with write
	I2C_write(0x00); // Command mode
	I2C_write(command);
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void ssd1306_data(uint8_t data) 
{
	I2C_start();
	
	I2C_write(I2C_ADDRESS << 1); // SSD1306 address with write
	I2C_write(0x40); // Data mode
	I2C_write(data);
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void ssd1306_setColumn(uint8_t start, uint8_t end) 
{
	I2C_start();

	I2C_write(I2C_ADDRESS << 1); // SSD1306 I2C address (write)
	I2C_write(0x00); // Command mode
	I2C_write(0x21); // Set Column Address command
	I2C_write(start); // Start column
	I2C_write(end);   // End column

	I2C_stop();
}
//------------------------------------------------------------------------------
void ssd1306_print(uint8_t row, uint8_t col, uint8_t text[]) 
{
	ssd1306_command(SET_PAGE_ADDR | row); // Set page address 
	ssd1306_setColumn(col, 127);									// Set column address
	
	while(*text)
	{ 
		uint8_t chr = *text++;

		if(chr != 194)		//° is implicitly split into 194 and 176 by the arduino c++ compiler
			writeChar(chr);
	}
}
//------------------------------------------------------------------------------
//										//Currently not working
void ssd1306_displayImage(uint16_t width, uint16_t height, const uint8_t *bitmap) 
{
	uint16_t index = 0;

	for(uint8_t page = 0; page < (height / 8); page++) 
	{
		ssd1306_command(0xB0 + page); // Set page address
		ssd1306_command(0x00);       	// Set lower column address
		ssd1306_command(0x10);       	// Set higher column address
		
		for(uint8_t col = 0; col < width; col++) 
		{
			ssd1306_data(bitmap[index++]);
		}
	}
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr)
{
	uint8_t chunk = 0;
	
	for(uint8_t col = 0; col < 5; col++)
	{
		chunk = (isascii(chr)) ? chars[chr - ' '][col] : customChars[0][col]; 
		ssd1306_data(chunk);	
	}
		
	ssd1306_data(0x00);														//Space 
}
//------------------------------------------------------------------------------
#endif