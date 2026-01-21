#ifndef HT16K33_C
#define	HT16K33_C
//------------------------------------------------------------------------------
#include "ht16k33.h"
//------------------------------------------------------------------------------
void ht16k33_init(uint8_t brightness)
{
	// Initialize I2C communication
	I2C_init();
	
	delay(5);  // Required after Power On reset to give time to initialize device
	
	ht16k33_on();  // Turn on the HT16K33
	ht16k33_setBrightness(brightness);  // Set brightness level (0-15)
	ht16k33_blink(0);  // Disable blinking
}
//------------------------------------------------------------------------------
void ht16k33_on(void)
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
	while(*text)
	{
		uint8_t chr = *text++;
		
		if(chr != 194)		//° is implicitly split into 194 and 176 by the arduino c++ compiler
		{
			writeChar(chr); 
		}
	}
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr)
{	
	uint16_t digit = getDigit(chr); //ascii to 14 seg

	I2C_write(digit);						//Lower byte  (D7 - D0)
	I2C_write(digit >> 8);					//Higher byte (D15 - D8)
}
//------------------------------------------------------------------------------
//          ascii to 16-segment display conversion
//------------------------------------------------------------------------------
uint16_t getDigit(uint8_t chr)
{
	uint16_t digit = 0;

	digit = (isprint(chr)) ? chars[chr - ' '] : custom_chars[0];  //custom _char is ° symbol
	
	return digit;
}
//------------------------------------------------------------------------------
#endif	/* HT16K33_H */