#ifndef HT16K33_C
#define	HT16K33_C
//------------------------------------------------------------------------------
#include "ht16k33.h"
//------------------------------------------------------------------------------
void ht16k33_init(uint8_t brightness)
{     
  i2c_init();           
	
  delay(5);               // Required after Power On reset to give time to initialize device
 
  ht16k33_on();
  ht16k33_setBrightness(brightness);   // Valid values from 0 - 15
  ht16k33_blink(0);            // Blink OFF
}
//------------------------------------------------------------------------------
void ht16k33_on()
{
  i2c_start();
	
  i2c_write(HT16K33_ADDRESS);
  i2c_write(OSCILLATOR_ON);          
	
  i2c_stop();
}
//------------------------------------------------------------------------------
void ht16k33_setBrightness(uint8_t num)
{   
  uint8_t level = ( num <= 15 ) ? num : 1;
	
  i2c_start();
 
  i2c_write(HT16K33_ADDRESS);
  i2c_write(DIGITAL_DIM | level);  // Dimming command. valid values are 0 - 15
 
  i2c_stop();
}
//------------------------------------------------------------------------------
void ht16k33_blink(uint8_t data)
{
  i2c_start();
	
  i2c_write(HT16K33_ADDRESS);
  i2c_write(DISPLAY_SETUP | (data << 1));  // Blinking / blanking command
	
  i2c_stop();
}
//------------------------------------------------------------------------------
void ht16k33_displayNum(int32_t number)
{
  uint8_t strNum[12];
  sprintf(strNum, "%8li", number);
	
  ht16k33_displayText(strNum);
}
//------------------------------------------------------------------------------
void ht16k33_displayText(uint8_t text[])
{
  i2c_start();
	
  i2c_write(HT16K33_ADDRESS);
  i2c_write(DISPLAY_MEMORY);     // Display data start address. Auto increments on every write.
  ht16k33_write(text);
	
  i2c_stop();
}
//------------------------------------------------------------------------------
void ht16k33_write(uint8_t text[])
{
  uint8_t chrPos = 0;
  int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};	
		
  setDpPos(dpPos, text);
	
  while(*text)
  {
	uint8_t chr = *text++;
	
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
  uint8_t digit = getDigit(chr, chrPos, dpPos); //ascii to 7 seg

  i2c_write(digit);				// Lower byte  (D7 - D0)
  i2c_write(0);					// Higher byte (D15 - D8) Unused in 7 seg display
}
//------------------------------------------------------------------------------
//          				ascii to 7 segment
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
  uint8_t digit = 0;

  digit = (isprint(chr)) ? chars[chr - ' '] : custom_chars[0];  // custom char is ° symbol
	
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
#endif	/* HT16K33_C */

