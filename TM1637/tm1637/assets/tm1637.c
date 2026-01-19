#ifndef TM1637_C
#define	TM1637_C
//------------------------------------------------------------------------------
#include "TM1637.h"
//------------------------------------------------------------------------------
void TM1637_init(uint8_t level)
{
	twoWire_init();    
	TM1637_setBrightness(level); //Valid brightness values: 0 - 8. 0 = display off.
}
//------------------------------------------------------------------------------
void TM1637_displayNum(signed int number)
{    
	uint8_t strNum[10];
	sprintf(strNum, "%4i", number);
	
	TM1637_displayNumText(strNum);
}
//------------------------------------------------------------------------------
void TM1637_displayNumText(uint8_t text[])
{    	
	TM1637_command(DISPLAY_MODE);    
	TM1637_write(text);
}
//------------------------------------------------------------------------------
void TM1637_setBrightness(uint8_t level)
{    
	TM1637_command(DISPLAY_CTRL + level); // Valid brightness values: 0 - 8. 0 = display off.
}
//------------------------------------------------------------------------------
void TM1637_write(uint8_t text[])
{
	uint8_t chrPos = 0, chr;
	int8_t dpPos[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
						
	getDpPos(dpPos, text);
	TM1637_initSend(DISPLAY_REG0);
	
	while(*text)
	{        
		chr = *text++;
		
		if(chr != '.' && chr != 194)      //° is implicitly split into 194 and 176 by the arduino c++ compiler 
		{
			writeChar(chr, chrPos, dpPos[chrPos]);
			chrPos++;
		}
	}
	
	twoWire_stop();
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
	twoWire_write( getDigit(chr, chrPos, dpPos) );
	twoWire_ack();
}
//------------------------------------------------------------------------------
void TM1637_command(uint8_t command)
{
	TM1637_initSend(command);
	twoWire_stop();
}
//------------------------------------------------------------------------------
void TM1637_initSend(uint8_t command)
{
	twoWire_start();
	twoWire_write(command);
	twoWire_ack();
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isdigit(chr)) ? digits[chr - '0'] : getCustomChar(chr);
					
	return (dpPos != -1 && charPos == dpPos) ? (digit | DECIMAL_POINT)  : digit;
}
//------------------------------------------------------------------------------
uint8_t getCustomChar(uint8_t chr)
{
	uint8_t i = 0, digit = 0x00;
  
	while(customChar[i])
	{
		 if(toupper(chr) == customChar[i])
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
#endif	/* TM1637_H */