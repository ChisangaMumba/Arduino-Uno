#ifndef SAA1064_C
#define	SAA1064_C
//------------------------------------------------------------------------------
#include "SAA1064.h"
//------------------------------------------------------------------------------
void SAA1064_init()
{     
	I2C_init();            

	I2C_start();

	I2C_write(SAA1064_ADDRESS);   
	I2C_write(CONTROL_REG);    
	I2C_write(DEVICE_CONFIG);    
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void SAA1064_displayInt(int16_t number)
{
	uint8_t strNum[6];
	sprintf(strNum,"%4i",number);

	SAA1064_displayText(strNum);
}
//------------------------------------------------------------------------------
void SAA1064_displayText(uint8_t text[])
{ 
	I2C_start();
	
	I2C_write(SAA1064_ADDRESS); // Device address
	I2C_write(DISPLAY_REG);     // Display data start address. Auto increments on every write.
	SAA1064_write(text);
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void SAA1064_write(uint8_t text[])
{
	uint8_t charPos = 0, dp = '.';
	int8_t dpPos = findPosChar(text, dp) - 1;  // dp: decimal point
	
	text = getLastCharAddr(text); // To write the Data backwards 
	
	while(*text)
	{
		uint8_t chr = *text--;
		
		if(chr != dp)
			writeChar(charPos++, dpPos, chr);   
	}	
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chrPos, int8_t dpPos, uint8_t chr)
{    
	uint8_t digit = getDigit(chrPos, dpPos, chr); // ascii to 7 seg

	I2C_write(digit);                     
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t charPos, int8_t dpPos, uint8_t chr)
{
	uint8_t digit = 0;
	
	digit = (isdigit(chr)) ? digits[chr - '0'] : getCustomChar(chr);
					
	return (dpPos != -1 && charPos == dpPos) ? digit + DECIMAL_POINT  : digit;
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
int8_t findPosChar(uint8_t chars[], uint8_t toFind)
{
	int8_t i = 0, pos = -1;

	for(i = 0; i < strlen(chars); i++)
	{
		if(chars[i] == toFind)
		{
			pos = i - 1;
			break;
		}
	}

	return pos;
}
//------------------------------------------------------------------------------
uint8_t* getLastCharAddr(uint8_t text[])
{
	uint8_t lastAddr =  strlen(text) - 1;  

	return text + lastAddr;
}
//------------------------------------------------------------------------------
#endif	/* SAA1064_H */