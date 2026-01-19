#ifndef HT16K33_C
#define	HT16K33_C
//------------------------------------------------------------------------------
#include "ht16k33.h"
//------------------------------------------------------------------------------
void ht16k33_init()
{     
	I2C_init();           
	
	delay(5);               //Required after Power On reset to give time to initialize device
 
	ht16k33_on();
	ht16k33_setBrightness(15);   //Valid values from 0 - 15
	ht16k33_blink(0);            //Blink OFF
}
//------------------------------------------------------------------------------
void ht16k33_on()
{
	I2C_start();
	
	I2C_write(HT16K33_ADDRESS);
	I2C_write(OSCILLATOR_ON);          
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void ht16k33_setBrightness(uint8_t num)
{   
  uint8_t level = ( num <= 15 ) ? num : 1;
	
  I2C_start();
 
  I2C_write(HT16K33_ADDRESS);
  I2C_write(DIGITAL_DIM | level);  // Dimming command. valid values are 0 - 15
 
  I2C_stop();
}
//------------------------------------------------------------------------------
void ht16k33_blink(uint8_t data)
{
	I2C_start();
	
	I2C_write(HT16K33_ADDRESS);
	I2C_write(DISPLAY_SETUP | (data << 1));  // Blinking / blanking command
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void ht16k33_displayNum(signed long int number)
{
	uint8_t strNum[12];
	sprintf(strNum, "%8li", number);
	
	ht16k33_displayText(strNum);
}
//------------------------------------------------------------------------------
void ht16k33_displayText(uint8_t text[])
{
	I2C_start();
	
	I2C_write(HT16K33_ADDRESS);
	I2C_write(DISPLAY_MEMORY);     //Display data start address. Auto increments on every write.
	ht16k33_write(text);
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void ht16k33_write(uint8_t text[])
{
	uint8_t chrPos = 0;
		
	while(*text)
	{
		uint8_t chr = *text++;
		
		if(chr != 194)		//° is implicitly split into 194 and 176 by the arduino c++ compiler
		{
			writeChar(chr, chrPos);
			chrPos++;
		}
	}
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr, uint8_t chrPos)
{	
	uint16_t digit = getDigit(chr, chrPos); //ascii to 14 seg

	I2C_write(digit);						//Lower byte  (D7 - D0)
	I2C_write(digit >> 8);					//Higher byte (D15 - D8)
}
//------------------------------------------------------------------------------
//          ascii to 14 segment
uint16_t getDigit(uint8_t chr, uint8_t chrPos)
{
	uint16_t digit = 0;

	//Standard ascii chars range 32 - 127.  minus first 32 or ' ' non-printable ascii characters (see ascii table)
	digit = (chr >= 32 && chr <= 127) ? chars[chr - ' '] : custom_chars[0];  //custom _char is ° symbol
	
	return digit;
}
//------------------------------------------------------------------------------
#endif	/* HT16K33_H */