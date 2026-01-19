#ifndef MAX7219_C
#define	MAX7219_C
//------------------------Dot Matrix LED  Driver--------------------------------
#include "MAX7219.h"
uint8_t CS = 10;
//------------------------------------------------------------------------------
void MAX7219_init(uint8_t noChips)
{
  pinMode(CS, OUTPUT);
  SPI_init();
  while(noChips)
        MAX7219_config(--noChips);
}
//------------------------------------------------------------------------------
void MAX7219_config(uint8_t chip)
{
  MAX7219_write(DECODE_MODE_REG,DISABLE_DECODE,chip);    
  MAX7219_write(INTESITY_REG,BRIGHTNESS,chip);     
  MAX7219_write(SCAN_LIMIT_REG,SCAN_ALL_DIGITS,chip);     
  MAX7219_write(SHUTDOWN_REG,NORMAL_OPERATION,chip);
  MAX7219_write(DISPLAY_TEST_REG,DISABLE_TEST,chip);   
}
//------------------------------------------------------------------------------
void MAX7219_write(uint8_t regName, uint8_t data, uint8_t chip)
{
  digitalWrite(CS, LOW);       //CS1 = 0
          
  SPI_write(regName); 
  SPI_write(data); 
  while(chip--)
       MAX7219_NoOperation();  //Used for daisy chained (Cascaded) arrangements
  
  digitalWrite(CS, HIGH);      //CS1 = 1
}
//------------------------------------------------------------------------------
void MAX7219_displayText(uint8_t* text)
{ 
  uint8_t col, chip = 0;
 
  while(*text)
  { 
		uint8_t chr = *text++;
    uint8_t row = chr - ' ';    //(Text-32)...because the first 32 ASCII character codes are none Printable (control chars)
    
    for(col = 0; col < 5; col++)
    {
			if(chr != '.')
			{
				MAX7219_write(col+1, chars[row][col], chip);
			}
    }
		
		//Display decimal point
		if(chr == '.')
		{
			MAX7219_write(col+2, 0x60, chip-1);  
			MAX7219_write(col+3, 0x60, chip-1);
		}
		else
				chip++;
  }
}
//----------Passes the data_ to the adjacent MAX7219 in the Daisy Chain---------
void MAX7219_NoOperation()
{
  SPI_write(NO_OP_REG);           
  SPI_write(0x00);                //Don't care (Can be any arbitrary value)
}
//------------------------------------------------------------------------------
#endif		