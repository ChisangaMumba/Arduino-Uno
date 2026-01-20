#ifndef MAX7219_C
#define	MAX7219_C
//------------------------Dot Matrix LED  Driver--------------------------------
#include "MAX7219.h"
uint8_t CS = 9;
//------------------------------------------------------------------------------
void MAX7219_init(uint8_t scanSize)
{
  SPI_init();
  pinMode(CS, OUTPUT);
     
  MAX7219_write(DECODE_MODE_REG, DISABLE_DECODE);    
  MAX7219_write(INTESITY_REG, BRIGHTNESS);     
  MAX7219_write(SCAN_LIMIT_REG, scanSize);     
  MAX7219_write(SHUTDOWN_REG, NORMAL_OPERATION);
}
//------------------------------------------------------------------------------
void MAX7219_write(uint8_t reg, uint8_t data)
{
  digitalWrite(CS, LOW);		//CS1 = 0; 
  
  SPI_write(reg); 
  SPI_write(data); 
  
  digitalWrite(CS, HIGH);		//CS1 = 1;
}
//------------------------------------------------------------------------------
void MAX7219_displayNumber(signed long number)
{   
  char strNum[10]; 
  sprintf(strNum, "%6li", number);
	
  MAX7219_displayText(strNum);
}
//------------------------------------------------------------------------------
void MAX7219_displayText(uint8_t text[])
{ 
  uint8_t chrPos = 0;
  int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};		
	
  getDpPos(dpPos, text);
	
  for(uint8_t i = 0; text[i]; i++)
  {   
    uint8_t chr = text[i];  
	
	if(chr != '.' && chr != 194)		//° is implicitly split into 194 and 176 by the arduino c++ compiler
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
	MAX7219_write(chrPos + 1, digit);
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isdigit(chr)) ? digits[chr - '0'] : getCustomChar(chr);
					
	return (dpPos != -1 && chrPos == dpPos) ? digit + DECIMAL_POINT  : digit;
}
//------------------------------------------------------------------------------
uint8_t getCustomChar(uint8_t chr)
{
	uint8_t i = 0, digit = 0x00;
  
	while(chars[i])
	{
		if(toupper(chr) == chars[i])
		{
			digit = charCode[i];
			break;
		}
		i++;
	}	
					
	return digit;			
}
//------------------------------------------------------------------------------
void getDpPos(int8_t dpPos[], uint8_t chars[])
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