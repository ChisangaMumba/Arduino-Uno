#ifndef SR_74HC595_C
#define	SR_74HC595_C
//------------------------------------------------------------------------------
#include "74HC595.h"
uint8_t CS1  = 10;
//------------------------------------------------------------------------------
void ShiftReg_init()
{
	pinMode(CS1, OUTPUT);
	digitalWrite(CS1, HIGH);       //CS1 = 1		//Deselect initially
}
//-------------------------First In First Out Send-------------------------------
void ShiftReg_FIFOSend(uint8_t text[])
{
	uint8_t chrPos = 3, chr;
	int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	getDpPos(dpPos, text);
		
	text = get_lastCharAddr(text);
	
	digitalWrite(CS1, LOW); 			//	CS1 = 0;
	
	while(*text)
	{
		chr = *text--;
		
		if(chr != '.')
		{
			writeChar(chr, chrPos, dpPos[chrPos]);
			chrPos--;
		}
	}
	
	digitalWrite(CS1, HIGH);			//	CS1 = 1; 
}
//--------------------------Last In First Out Send-----------------------------
void ShiftReg_LIFOSend(uint8_t text[])
{ 
  	uint8_t chrPos = 3, chr;
	int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	getDpPos(dpPos, text);

	digitalWrite(CS1, LOW);			//	CS1 = 0;
  
	while(*text)
	{ 
		chr = *text++;
		
		if(chr != '.')
		{
			writeChar(chr, chrPos+1, dpPos[chrPos+1]);
			chrPos--;
		}
	}
	
	digitalWrite(CS1, HIGH);		//	CS1 = 1; 
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr, uint8_t charPos, int8_t dpPos)
{
	uint8_t digit = getDigit(chr, charPos, dpPos);
	SPI_write(digit);
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isdigit(chr)) ? digits[chr - '0'] : getCustomChar(chr);
					
	return (dpPos != -1 && charPos == dpPos) ? (digit & DECIMAL_POINT) : digit;
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
			dpPos[pos - 1] = pos - 1;
		}
		else
			{
				pos++;
			}
	}
}
//------------------------------------------------------------------------------
uint8_t* get_lastCharAddr(uint8_t text[])
{
  uint8_t lastAddr =  strlen(text) - 1;  
  
  return text + lastAddr;
}
//------------------------------------------------------------------------------
#endif	