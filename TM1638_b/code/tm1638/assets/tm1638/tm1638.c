#ifndef TM1638_C
#define TM1638_C
//-----------------------------------------------------------------------------------
#include "tm1638.h"
//-----------------------------------------------------------------------------------
void tm1638_init(uint8_t brightness)
{
  serialInit();

  tm1638_setBrightness(brightness);
  tm1638_clearDisplay();
  tm1638_command(0x44);		// single address mode
}
//-----------------------------------------------------------------------------------
void tm1638_command(uint8_t command)
{
  digitalWrite(STB, LOW);
  
  serialOut(LSBFIRST, command);
  
  digitalWrite(STB, HIGH);
}
//-----------------------------------------------------------------------------------
void tm1638_data(uint8_t reg, uint8_t data)
{
  digitalWrite(STB, LOW);
  
  serialOut(LSBFIRST, reg);
  serialOut(LSBFIRST, data);
  
  digitalWrite(STB, HIGH);
}
//-----------------------------------------------------------------------------------
void tm1638_setBrightness(uint8_t brightness)
{
  tm1638_command(0x88 + brightness);	
}
//-----------------------------------------------------------------------------------
void tm1638_clearDisplay(void)
{
  tm1638_command(0x40);   // auto increment mode: only for resetting both LEDs and 7 seg displays
  digitalWrite(STB, LOW);
  
  serialOut(LSBFIRST, DISPLAY_REG0);
  for(uint8_t i = 0; i < 16; i++) 
	  serialOut(LSBFIRST, 0x00);
  
  digitalWrite(STB, HIGH);
}
//-----------------------------------------------------------------------------------
void tm1638_print(const char* format, ...)
{
  char str[20];
  va_list args;
  va_start(args, format);
  vsnprintf(str, sizeof(str), format, args);
  va_end(args);
  
  tm1638_string((uint8_t*)str);
}
//-----------------------------------------------------------------------------------
void tm1638_string(uint8_t str[])
{
  uint8_t chr, chrPos = 0, reg = 0;
  int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  setDpPos(dpPos, str);
	
  pinMode(DIO, OUTPUT);  
  digitalWrite(STB, LOW);
	
  while(*str)
  {
    chr = *str++;
      
    if(chr != '.' && chr != 194)  // ° is implicitly split into 194 and 176 by the arduino c++ compiler 
    {	   
      writeChar(reg, chr, chrPos, dpPos[chrPos]);
      chrPos++;
      reg += 2;
    }
  }
  
  digitalWrite(STB, HIGH);
}
//-----------------------------------------------------------------------------------
void tm1638_writeLed(uint8_t pos, uint8_t data)
{
  uint8_t ledPos[8] = { 0xC1, 0xC3, 0xC5, 0xC7, 0xC9, 0xCB, 0xCD, 0xCF };
  pinMode(DIO, OUTPUT);
  
  tm1638_command(0x44); 
  tm1638_data(ledPos[pos], data);  
}
//-----------------------------------------------------------------------------------
void tm1638_pulseLed(uint8_t pos)
{
  tm1638_writeLed(pos, 1);
  delay(200);
  tm1638_writeLed(pos, 0);
}
//-----------------------------------------------------------------------------------
uint8_t tm1638_readButtons(void)
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
  uint8_t buttonPos = 0x01;
  
  for(uint8_t i = 0; i < 8; i++)
  { 
    if(buttons == (buttonPos << i)) 
    {
      tm1638_pulseLed(i);
    }
  }
}
//-----------------------------------------------------------------------------------
void writeChar(uint8_t reg, uint8_t chr, uint8_t chrPos, int8_t dpPos)
{
  uint8_t digit = getDigit(chr, chrPos, dpPos);
  tm1638_data(DISPLAY_REG0 + reg, digit);	
}
//-----------------------------------------------------------------------------------
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos)
{
  uint8_t digit = 0;
	
  digit = (isprint(chr)) ? chars[chr - ' '] : custom_chars[0];
					
  return ((dpPos != -1) && (charPos == dpPos)) ? (digit + DECIMAL_POINT) : digit;
}
//-----------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------
#endif