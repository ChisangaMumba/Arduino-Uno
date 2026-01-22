#ifndef MAX7219_C
#define	MAX7219_C
//------------------------------------------------------------------------------
#include "max7219.h"
//------------------------------------------------------------------------------
void max7219_init(uint8_t noChips)
{
  spi_init();
  
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);   // CS1 = 1 (unselect initially)

  while(noChips)
    max7219_config(--noChips);
}
//------------------------------------------------------------------------------
void max7219_config(uint8_t chip)
{
  max7219_write(DECODE_MODE_REG,DISABLE_DECODE,chip);    
  max7219_write(INTESITY_REG,BRIGHTNESS,chip);     
  max7219_write(SCAN_LIMIT_REG,SCAN_ALL_DIGITS,chip);     
  max7219_write(SHUTDOWN_REG,NORMAL_OPERATION,chip);
  max7219_write(DISPLAY_TEST_REG,DISABLE_TEST,chip);   
}
//------------------------------------------------------------------------------
void max7219_write(uint8_t regName, uint8_t data, uint8_t chip)
{
  digitalWrite(CS, LOW);      // CS = 0

  spi_write(regName);
  spi_write(data);
  while(chip--)
      max7219_NoOperation();  // Used for daisy chained (Cascaded) arrangements
  
  digitalWrite(CS, HIGH);     // CS = 1
}
//------------------------------------------------------------------------------
void max7219_displayNum(int32_t number)
{
  uint8_t numStr[15]; // Buffer for number string, adjust size as needed

  sprintf(numStr, "%ld", number);

  max7219_displayText(numStr);
}
//------------------------------------------------------------------------------
void max7219_displayText(uint8_t * text)
{ 
  uint8_t chrPos = 0, chr;
  int8_t dpPos[18] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; 
		
	setDpPos(dpPos, text);
 
  while(*text)
  { 
    chr = *text++; // Get the current character and increment the pointer
    
    
    if(chr != '.' && (chr != 194)) // ascii 194 is an extra character created by the degree ° symbol
    {
      writeChar(chr, chrPos, dpPos[chrPos]);
      chrPos++; 
    } 
      
  }
}
//----------Passes the data to the adjacent max7219 in the Daisy Chain---------
void max7219_NoOperation(void)
{
  spi_write(NO_OP_REG);
  spi_write(0x00);      // Don't care (Can be any arbitrary 8 bit value)  
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
  uint8_t chip = chrPos / 8; // Determine which chip to write to based on character position
  uint8_t chrAddr = chrPos % 8; // valid character positions range from 0-7 for each chip
  uint8_t digit = getDigit(chr, chrPos, dpPos);
	
  max7219_write(chrAddr + 1, digit, chip); // character address is 1-8 for each chip
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isprint(chr)) ? chars[chr - ' '] : custom_chars[0];
					
	return (dpPos != -1 && chrPos == dpPos) ? digit + DECIMAL_POINT : digit;
} 
//------------------------------------------------------------------------------
void setDpPos(int8_t dpPos[], uint8_t chars[])
{
	uint8_t i, pos = 0; 
	
	for(i = 0; chars[i]; i++)
  {
    if(chars[i] == '.')
		{
			dpPos[pos-1] = pos - 1;
		}
		else
				{
					pos++;
				}
  }
}
//------------------------------------------------------------------------------
#endif		