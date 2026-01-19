#ifndef TM1638_C
#define TM1638_C
//-----------------------------------------------------------------------------------
uint8_t STB = 8, CLK = 9, DIO = 10; 
//-----------------------------------------------------------------------------------
#include "serial.h"
#include "tm1638.h"
//-----------------------------------------------------------------------------------
void TM1638_init(uint8_t brightness)
{
  TM1638_setBrightness(brightness);
  TM1638_clearDisplay();
  TM1638_command(0x44);		// single address mode
}
//-----------------------------------------------------------------------------------
void TM1638_command(uint8_t command)
{
  digitalWrite(STB, LOW);
  
  serialOut(LSBFIRST, command);
  
  digitalWrite(STB, HIGH);
}
//-----------------------------------------------------------------------------------
void TM1638_data(uint8_t reg, uint8_t data)
{
  digitalWrite(STB, LOW);
  
  serialOut(LSBFIRST, reg);
  serialOut(LSBFIRST, data);
  
  digitalWrite(STB, HIGH);
}
//-----------------------------------------------------------------------------------
void TM1638_setBrightness(uint8_t brightness)
{
  TM1638_command(0x88 + brightness);	
}
//-----------------------------------------------------------------------------------
void TM1638_clearDisplay()
{
  TM1638_command(0x40);   // auto increment mode: only for resetting both LEDs and 7 seg displays
  digitalWrite(STB, LOW);
  
  serialOut(LSBFIRST, DISPLAY_REG0);
  for(uint8_t i = 0; i < 16; i++) 
	  serialOut(LSBFIRST, 0x00);
  
  digitalWrite(STB, HIGH);
}
//-----------------------------------------------------------------------------------
void TM1638_writeDisplay(uint8_t text[])
{
  uint8_t chr, chrPos = 0, reg = 0;
  int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  getDpPos(dpPos, text);
	
  pinMode(DIO, OUTPUT);  
  digitalWrite(STB, LOW);
	
  while(*text)
  {
	chr = *text++;
		
	if(chr != '.' && chr != 194)  //° is implicitly split into 194 and 176 by the arduino c++ compiler 
    {	   
	  writeChar(reg, chr, chrPos, dpPos[chrPos]);
	  chrPos++;
	  reg += 2;
	}
  }
  
  digitalWrite(STB, HIGH);
}
//-----------------------------------------------------------------------------------
void TM1638_writeLed(uint8_t pos, uint8_t data)
{
  uint8_t ledPos[8] = { 0xC1, 0xC3, 0xC5, 0xC7, 0xC9, 0xCB, 0xCD, 0xCF };
  pinMode(DIO, OUTPUT);
  
  TM1638_command(0x44); 
  TM1638_data(ledPos[pos], data);  
}
//-----------------------------------------------------------------------------------
void TM1638_pulseLed(uint8_t pos)
{
  TM1638_writeLed(pos, 1);
  delay(200);
  TM1638_writeLed(pos, 0);
}
//-----------------------------------------------------------------------------------
uint8_t TM1638_readButtons()
{
  uint8_t buttons = 0;

  digitalWrite(STB, LOW);
  serialOut(LSBFIRST, 0x42);
  pinMode(DIO, INPUT);
  
  for(uint8_t i = 0; i <= 3; i++)
  {
    buttons += serialIn(LSBFIRST) << i;
  }

  pinMode(DIO, OUTPUT);
  digitalWrite(STB, HIGH);

  return buttons;
}
//-----------------------------------------------------------------------------------
void ledFeedback(uint8_t buttons)
{
  uint8_t value[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
  
  for(uint8_t i = 0; i < 8; i++)
  {
	if(buttons == value[i]) 
	  TM1638_pulseLed(i);
  }
}
//-----------------------------------------------------------------------------------
void writeChar(uint8_t reg, uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
  TM1638_data(DISPLAY_REG0 + reg, getDigit(chr, chrPos, dpPos));	
}
//-----------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos)
{
  uint8_t digit = 0;
	
  digit = (isdigit(chr)) ? digits[chr - '0'] : getCustomChar(chr);
					
  return (dpPos != -1 && charPos == dpPos) ? (digit + DECIMAL_POINT) : digit;
}
//-----------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------
#endif