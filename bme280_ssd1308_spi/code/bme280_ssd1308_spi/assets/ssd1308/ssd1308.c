#ifndef SSD1308_C
#define SSD1308_C
//------------------------------------------------------------------------------
#include "ssd1308.h"
//------------------------------------------------------------------------------
void ssd1308_init(void) 
{
	spi_init(); 

	pinMode(CS1, OUTPUT);
	pinMode(RST, OUTPUT);
	pinMode(DC, OUTPUT);

	ssd1308_reset();

	ssd1308_command(SSD1308_DISPLAY_OFF); // Display off
	ssd1308_command(0xD5); 								// Set display clock divide ratio
	ssd1308_command(0x80); 								// Suggested ratio
	ssd1308_command(0xA8); 								// Set multiplex ratio
	ssd1308_command(0x3F); 								// 1/64 duty
	ssd1308_command(0xD3); 								// Set display offset
	ssd1308_command(0x00); 								// No offset
	ssd1308_command(SSD1308_MEMORY_MODE); // Memory addressing mode
	ssd1308_command(0x00); 								// Horizontal addressing mode
	ssd1308_command(SSD1308_DISPLAY_RAM); // Output follows RAM content
	ssd1308_command(SSD1308_DISPLAY_ON); 	// Display on
}
//------------------------------------------------------------------------------
void ssd1308_command(uint8_t command) 
{
	digitalWrite(CS1, LOW);		//CS1 = 0;
	
	digitalWrite(DC, LOW);		//DC = 0; //Commands
	spi_write(command);
	
	digitalWrite(CS1, HIGH);	//CS1 = 1;
}
//------------------------------------------------------------------------------
void ssd1308_data(uint8_t data_) 
{
	digitalWrite(CS1, LOW);		//CS1 = 0;
	
	digitalWrite(DC, HIGH);		//DC = 1; //Data
	spi_write(data_);
	
	digitalWrite(CS1, HIGH);	//CS1 = 1;
}
//------------------------------------------------------------------------------
void ssd1308_setColumn(uint8_t start, uint8_t end) 
{
	ssd1308_command(0x21); 	// Set Column Address command
	ssd1308_command(start); // Start column
	ssd1308_command(end);   // End column
}
//------------------------------------------------------------------------------
void ssd1308_print(uint8_t row, uint8_t col, uint8_t text[]) 
{
	ssd1308_command(SSD1308_SET_PAGE_ADDR | row); // Set page address 
	ssd1308_setColumn(col, 127);									// Set column address
	
	while(*text)
	{
		uint8_t chr = *text++;

		if(chr != 194)						// ° is implicitly split into 194 and 176 by the arduino c++ compiler
			writeChar(chr);
	}
}
//------------------------------------------------------------------------------
//										//Currently not working
void ssd1308_displayImage(uint16_t width, uint16_t height, const uint8_t *bitmap) 
{
	uint8_t page, col;
	uint16_t index = 0;

	for(page = 0; page < (height / 8); page++) 
	{
		ssd1308_command(0xB0 + page); // Set page address
		ssd1308_command(0x00);       	// Set lower column address
		ssd1308_command(0x10);       	// Set higher column address
		
		for(col = 0; col < width; col++) 
		{
			ssd1308_data(bitmap[index++]);
		}
	}
}
//------------------------------------------------------------------------------
void ssd1308_reset(void)
{
	digitalWrite(RST, LOW);	//RST = 0;
	delay(10);
	digitalWrite(RST, HIGH);	//RST = 1;
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr)
{
	uint8_t col, font;
	
	for(col = 0; col < 5; col++)
	{
		font = (isprint(chr)) ? chars[chr - ' '][col] : customChars[0][col];
		ssd1308_data(font);
	}
		
	ssd1308_data(0x00);	//Space 
}
//------------------------------------------------------------------------------
#endif