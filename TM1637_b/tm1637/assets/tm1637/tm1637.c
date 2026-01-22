#ifndef TM1637_C
#define	TM1637_C
//------------------------------------------------------------------------------
#include "tm1637.h"
//------------------------------------------------------------------------------
void tm1637_init(uint8_t level)
{
	twoWire_init();  
	tm1637_command(DISPLAY_MODE);   
	tm1637_setBrightness(level); //Valid brightness values: 0 - 8. 0 = display off.
}
//------------------------------------------------------------------------------
void tm1637_setBrightness(uint8_t level)
{    
	tm1637_command(DISPLAY_CTRL + level); // Valid brightness values: 0 - 8. 0 = display off.
}
//------------------------------------------------------------------------------
void tm1637_print(const char* format, ...)
{
	char str[10];	// Adjust size as needed

	va_list args;	// Initialize variable argument list
	va_start(args, format); // Start processing arguments
	vsnprintf(str, sizeof(str), format, args); // Format the string
	va_end(args); // End processing arguments
	
	tm1637_string(str); // Display the formatted string
}
//------------------------------------------------------------------------------
void tm1637_string(uint8_t text[])
{
	uint8_t chrPos = 0, chr;
	int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
						
	setDpPos(dpPos, text);
	tm1637_initSend(DISPLAY_REG0);
	
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
void tm1637_command(uint8_t command)
{
	tm1637_initSend(command);
	twoWire_stop();
}
//------------------------------------------------------------------------------
void tm1637_initSend(uint8_t command)
{
	twoWire_start();
	twoWire_write(command);
	twoWire_ack();
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isprint(chr)) ? chars[chr - ' '] : custom_chars[0]; // Return blank for non-printable characters
					
	return (dpPos != -1 && charPos == dpPos) ? (digit | DECIMAL_POINT)  : digit;
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
#endif	/* tm1637_H */