#ifndef MAX7219_C
#define	MAX7219_C
//------------------------Dot Matrix LED  Driver--------------------------------
#include "max7219.h"
//------------------------------------------------------------------------------
void max7219_init(uint8_t scanSize)
{
  spi_init();
  pinMode(CS, OUTPUT);
     
  max7219_write(DECODE_MODE_REG, DISABLE_DECODE);    
  max7219_write(INTESITY_REG, BRIGHTNESS);     
  max7219_write(SCAN_LIMIT_REG, scanSize);     
  max7219_write(SHUTDOWN_REG, NORMAL_OPERATION);
}
//------------------------------------------------------------------------------
void max7219_write(uint8_t reg, uint8_t data)
{
  digitalWrite(CS, LOW);		// CS = 0; 
  
  spi_write(reg); 
  spi_write(data); 
  
  digitalWrite(CS, HIGH);		// CS = 1;
}
//------------------------------------------------------------------------------
void max7219_displayNumber(int32_t number)
{   
  uint8_t strNum[10]; 
  sprintf(strNum, "%6li", number);
	
  max7219_displayText(strNum);
}
//------------------------------------------------------------------------------
void max7219_displayText(uint8_t text[])
{ 
  uint8_t chrPos = 0, i = 0;	
  int8_t  dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

  setDpPos(dpPos, text);
	
  while(text[i])
  {   
    uint8_t chr = text[i++];  
    
	if(chr != '.' && chr != 194)		// ° is implicitly split into 194 and 176 by the arduino c++ compiler
	{
		writeChar(chr, chrPos, dpPos[chrPos]);
		chrPos++;
	}
  }

}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
  uint8_t digit = getDigit(chr, chrPos, dpPos);
  max7219_write(chrPos + 1, digit);
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
  uint8_t digit = 0;
	
  digit = (isprint(chr)) ? chars[chr - ' '] : custom_chars[0]; // Default to first custom character if not printable
					
  return (dpPos != -1 && chrPos == dpPos) ? digit + DECIMAL_POINT  : digit;
}
//------------------------------------------------------------------------------
void setDpPos(int8_t dpPos[], uint8_t chars[])
{
  uint8_t pos = 0; 
	
  for(uint8_t i = 0; chars[i]; i++)
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