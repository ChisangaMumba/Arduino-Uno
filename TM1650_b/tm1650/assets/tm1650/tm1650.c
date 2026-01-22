#ifndef TM1650_C
#define TM1650_C
//-----------------------------------------------------------------------------------
#include "tm1650.h"
//-----------------------------------------------------------------------------------
void tm1650_init(uint8_t level) 
{
  I2C_init();
  tm1650_clear();
  tm1650_displayOn(level);                 // Enable display and set brightness
}
//-----------------------------------------------------------------------------------
void tm1650_data(uint8_t address, uint8_t data) 
{
  I2C_start();
  I2C_write(address << 1);        // Send the I2C address with the write bit      
  I2C_write(data);         
  I2C_stop();
}
//-----------------------------------------------------------------------------------
void tm1650_clear(void)
{
  for(uint8_t i = 0; i < 4; i++) 
  {
    tm1650_data(TM1650_ADDRESS_BASE + i, 0x00);     // Clear all digits. Keep the display on.
  }
}
//-----------------------------------------------------------------------------------
void tm1650_displayOn(uint8_t brightness)
{
  for(uint8_t i = 0; i < 4; i++) 
  {
    tm1650_data(TM1650_DCTRL_BASE + i, brightness);
  }
}
//-----------------------------------------------------------------------------------
void tm1650_print(const char* format, ...)
{
  char str[10];

  va_list args;					// Declare a va_list variable
  va_start(args, format);	// Initialize the va_list variable
  vsnprintf(str, sizeof(str), format, args); // Use vsprintf to print with the provided format and variadic arguments
  va_end(args);
  
  tm1650_string(str);
}		
//-----------------------------------------------------------------------------------
void tm1650_string(char str[]) 
{
	uint8_t chrPos = 0, chr;
	int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; // Reset Decimal point Pos array
						
	setDpPos(dpPos, str);
	
	while(*str)
	{        
		chr = *str++;
		
		if(chr != '.' && chr != 194)      //° is implicitly split into 194 and 176 by the arduino c++ compiler 
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
  tm1650_data(TM1650_ADDRESS_BASE + chrPos, digit);
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isprint(chr)) ? chars[chr - ' '] : custom_chars[0];
					
	return ((dpPos != -1) && (charPos == dpPos)) ? (digit | DECIMAL_POINT)  : digit;
}
//------------------------------------------------------------------------------
void setDpPos(int8_t dpPos[], char str[])
{
	uint8_t i, pos = 0; 
	
	for(i = 0; str[i]; i++)
	{
		if(str[i] == '.')
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