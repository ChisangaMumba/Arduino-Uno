#ifndef TM162x_C
#define TM162x_C
//-----------------------------------------------------------------------------------
#include "tm162x.h"
//-----------------------------------------------------------------------------------
void tm162x_init(void)
{
  serialInit();
  delay(50);

  tm162x_command(CMD_SYS_EN);		
  tm162x_command(CMD_RC_32K);		
  //tm162x_command(CMD_BIAS_COM);     // Only for HT1621 or TM1621
  tm162x_command(CMD_LCD_OFF);		
  tm162x_setDisplay(CLEAR);
  tm162x_command(CMD_LCD_ON);  // Should turn it back on	
  delay(1000);
}
//-----------------------------------------------------------------------------------
void tm162x_command(uint8_t command)
{
  digitalWrite(CS, LOW);
  
  serialOut(MSBFIRST,   0b100, 3);
  serialOut(MSBFIRST, command, 8);
  serialOut(MSBFIRST,       1, 1);
  
  digitalWrite(CS, HIGH);
}
//-----------------------------------------------------------------------------------
void tm162x_data(uint8_t addr, uint8_t sdata)
{
  // Note: bits needs to be a multiple of 4 as data is in nibbles
  digitalWrite(CS, LOW);
  
  serialOut(MSBFIRST, 0b101, 3);
  serialOut(MSBFIRST,  addr, 6);
  serialOut(LSBFIRST, sdata, 4);
  
  digitalWrite(CS, HIGH);
}
//-----------------------------------------------------------------------------------
void tm162x_setDisplay(uint8_t state)
{
  // TM1622 or HT1622 has 64 possible 4-bit addresses
  for(uint8_t i = 0; i < 64; i++)
  {
    tm162x_data(i, (state) ? 0x0F : 0x00);
  }
}
//-----------------------------------------------------------------------------------
void tm162x_print(const char* format, ...)
{
  char str[20];
  
  va_list args;
  va_start(args, format);
  vsnprintf(str, sizeof(str), format, args);
  va_end(args);
  
  tm162x_string((uint8_t*)str);
}
//-----------------------------------------------------------------------------------
void tm162x_string(uint8_t str[])
{
  uint8_t chrPos = 0, chr;
						
	while(*str)
	{        
		chr = *str++;
		
		if(chr != 194)      //° is implicitly split into 194 and 176 by the arduino c++ compiler 
		{
			writeChar(chr, chrPos);     // -1 indicates no decimal point
			chrPos++;
		}
	}
}
//-----------------------------------------------------------------------------------
void writeChar(uint8_t chr, uint8_t chrPos)
{
  uint16_t digit = getDigit(chr);

  for(uint8_t n = 0; n < 4; n++)
  {
    tm162x_data(nibbleAddr[chrPos] - n, digit >> (n * 4));
  }
}
//-----------------------------------------------------------------------------------
uint16_t getDigit(uint8_t chr)
{
	uint16_t digit = 0;
	
	digit = (isprint(chr)) ? chars[chr - ' '] : custom_chars[0];
					
	return digit;
}
//-----------------------------------------------------------------------------------
#endif