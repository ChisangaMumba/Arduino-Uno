#ifndef NOKIA_3310_GLCD_C
#define NOKIA_3310_GLCD_C
//------------------------------------------------------------------------------
uint8_t DC  = 9;
uint8_t RST = 8;
//------------------------------------------------------------------------------
#include "nokia_glcd.h"
//------------------------------------------------------------------------------
void LCD_init()
{
  SPI_init();

  pinMode(DC, OUTPUT);
  pinMode(RST, OUTPUT);
  
  LCD_reset();
  LCD_command(EXTENDED_COMMANDS);
  LCD_command(CONTRAST);
  LCD_command(TEMP_COEFFIECIENT);
  LCD_command(BIAS_MODE); 
  LCD_command(BASIC_COMMANDS);
  LCD_command(ALL_SEGS_ON);
	
  LCD_fill(FILL);
  LCD_fill(CLEAR);
}
//------------------------------------------------------------------------------
void LCD_address(uint8_t row, uint8_t col)
{	
  LCD_command(ROW0 | row);
  LCD_command(COL0 | (col * 6)); 
}
//------------------------------------------------------------------------------
void LCD_command(uint8_t command)
{
  digitalWrite(CS, LOW);		//CS = 0
	
  digitalWrite(DC, LOW);		//DC = 0 Instruction Register ( commands ). Data/Command pin, D/C=1 - Data, D/C = 0 - Command
  SPI_write(command); 
	
  digitalWrite(CS, HIGH); 		//CS = 1
}
//------------------------------------------------------------------------------
void LCD_string(uint8_t row, uint8_t col, uint8_t text[])
{
  LCD_address(row, col);  
  
  digitalWrite(CS, LOW);		//CS = 0
	
  digitalWrite(DC, HIGH);		//DC = 1 Data Register  ( Strings and characters ). Data/Command pin, D/C=1 - Data, D/C = 0 - Command
  while(*text)
  {
	  writeChar(*text++); 
    SPI_write(SPACE);
  }

  digitalWrite(CS, HIGH);		//CS = 1
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr)
{  
	for(uint8_t col = 0; col < 5; col++)
	{
		if(chr >= 32 && chr <= 127)						//Standard ascii Printable chars range 32 - 127 or 0 - 95 (after subtraction). degree symbol num ° is 176 or 144 after subtraction
			SPI_write(chars[chr - ' '][col]);		//(' ' = 32) chr - 32...because the first 32  ASCII character codes are none Printable (control chars)
		else
        if(chr == 176)								        //° degree symbol
          SPI_write(customChars[0][col]); 		//Custom Char is ° symbol
	}
}
//------------------------------------------------------------------------------
void LCD_image(const uint8_t *image)
{	
	digitalWrite(CS, LOW);			//CS = 0															
	
	digitalWrite(DC, HIGH); 		//DC = 1 Data Register ( Strings and characters ). Data/Command pin, D/C=1 - Data, D/C = 0 - Command
	for(int i = 0; i < 504; i++)
		SPI_write(image[i]);
	
	digitalWrite(CS, HIGH);			//CS = 1
}
//------------------------------------------------------------------------------
void LCD_fill(uint8_t data)
{	
	digitalWrite(CS, LOW);			//CS = 0															
	
	digitalWrite(DC, HIGH);			//DC = 1 //Data Register ( Strings and characters ). Data/Command pin, D/C=1 - Data, D/C = 0 - Command
	for(int i = 0; i < 504; i++)
		SPI_write(data);
	
	digitalWrite(CS, HIGH);			//CS = 1 
}
//------------------------------------------------------------------------------
void LCD_reset()
{
	digitalWrite(RST, LOW);			//RST = 0
	delay(100);
	digitalWrite(RST, HIGH);		//RST = 1
}
//------------------------------------------------------------------------------
#endif