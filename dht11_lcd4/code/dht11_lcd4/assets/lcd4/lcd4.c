#ifndef LCD4_C
#define	LCD4_C
//------------------------------------------------------------------------------
#include "lcd4.h"
//-----------------------Follow Datasheet instructions--------------------------
void lcd_init(void)
{
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);

  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  lcd_command(home);
  lcd_command(function_set4);   
  lcd_command(display_on);      
  lcd_command(auto_increment);
}
//------------------------------------------------------------------------------
void lcd_command(uint8_t command)
{
  digitalWrite(RS, LOW);          //  RS = 0;     //  Instruction register ( commands ).
  lcd_sendBits(command);
}
//------------------------------------------------------------------------------
void lcd_data(uint8_t data)
{
  digitalWrite(RS, HIGH);         //  RS = 1;     //  Data register  ( strings and characters ).
  lcd_sendBits(data);
}
//------------------------------------------------------------------------------
void lcd_string(uint8_t row, uint8_t column, uint8_t text[])
{
  lcd_command(rowAddr[row] + column);  // Set coordinates.

  while(*text)  // Loop until null terminator.
  {
    uint8_t chr = *text++;
		
		if(chr == 176)    // 176 is ° in Extended ascii
			chr = 0xDF;     //223d is the value of ° symbol in Hitachi HD44780 lcds
		
		if(chr != 194)	  //° is implicitly split into 194 and 176 by the arduino c++ compiler
      lcd_data(chr);  // Increment pointer to next character.
  }
}
//------------------------------------------------------------------------------
void lcd_sendBits(uint8_t data)
{
  // Higher Nibble
  digitalWrite(D7, getBit(7, data, LSBFIRST));  
  digitalWrite(D6, getBit(6, data, LSBFIRST));   
  digitalWrite(D5, getBit(5, data, LSBFIRST));   
  digitalWrite(D4, getBit(4, data, LSBFIRST));   
  latch();
  
  // Lower Nibble
  digitalWrite(D7, getBit(3, data, LSBFIRST));
  digitalWrite(D6, getBit(2, data, LSBFIRST));
  digitalWrite(D5, getBit(1, data, LSBFIRST));
  digitalWrite(D4, getBit(0, data, LSBFIRST));
  latch();

  /*
  // Higher Nibble
  digitalWrite(D7, getBit(7, data, MSBFIRST));  
  digitalWrite(D6, getBit(6, data, MSBFIRST));   
  digitalWrite(D5, getBit(5, data, MSBFIRST));   
  digitalWrite(D4, getBit(4, data, MSBFIRST));   
  latch();
  
  // Lower Nibble
  digitalWrite(D7, getBit(3, data, MSBFIRST));
  digitalWrite(D6, getBit(2, data, MSBFIRST));
  digitalWrite(D5, getBit(1, data, MSBFIRST));
  digitalWrite(D4, getBit(0, data, MSBFIRST));
  latch();
  */
}
//------------------------------------------------------------------------------
uint8_t getBit(uint8_t pos , uint8_t data, uint8_t dir = LSBFIRST)
{ 
  uint8_t pbit;
  
  switch(dir)
  {
    case(LSBFIRST): pbit = (data & (0x01 << pos)) ? HIGH : LOW; break;      // LSB first
    case(MSBFIRST): pbit = (data & (0x80 >> (7-pos))) ? HIGH : LOW; break;  // MSB first		
  }

  return pbit;
}
//------------------------------------------------------------------------------
void latch()
{
  digitalWrite(EN, HIGH);           //  EN  = 1;
  delay(5);
  digitalWrite(EN, LOW);            //  EN = 0;
}
//------------------------------------------------------------------------------
#endif