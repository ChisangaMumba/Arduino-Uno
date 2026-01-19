#ifndef TM1650_C
#define TM1650_C
//-----------------------------------------------------------------------------------
#include "TM1650.h"
//-----------------------------------------------------------------------------------
void tm1650_init() 
{
  // Wire.begin();                        // For hardware I2C. join I2C bus (address optional for master)

  I2C_init();
  tm1650_clear();
  tm1650_displayOn(0x07);                 // Enable display and set brightness
}
//-----------------------------------------------------------------------------------
void tm1650_data(uint8_t address, uint8_t data) 
{
  /*
  // For hardware I2C
  Wire.beginTransmission(address); // join I2C bus (address optional for master)
  Wire.write(data);
  Wire.endTransmission();
  */

  I2C_start();
  I2C_write(address << 1);        // Send the I2C address with the write bit      
  I2C_write(data);         
  I2C_stop();
}
//-----------------------------------------------------------------------------------
void tm1650_clear()
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
void tm1650_displayNum(int16_t number) 
{
  uint8_t strNum[10];
  sprintf(strNum, "%4i", number);
  
  tm1650_displayStrNum(strNum);
}
//-----------------------------------------------------------------------------------
void tm1650_displayStrNum(char text[]) 
{
	uint8_t chrPos = 0, count = 0, chr;
	int8_t dpPos[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
						
	getDpPos(dpPos, text);
	
	for(uint8_t i = 0; text[i]; i++)
	{        
		chr = text[i];
		
		if(chr != '.' && chr != 194)      //° is implicitly split into 194 and 176 by the arduino c++ compiler 
		{
			writeChar(count, chr, chrPos, dpPos[chrPos]);
			chrPos++;
      count++;
		}
	}
}
//------------------------------------------------------------------------------
void writeChar(uint8_t count, uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
  uint8_t digit = getDigit(chr, chrPos, dpPos);
  tm1650_data(TM1650_ADDRESS_BASE + count, digit);
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
#endif