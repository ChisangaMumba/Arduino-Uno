#ifndef LCD8_C
#define	LCD8_C
//------------------------------------------------------------------------------
#include "lcd8.h"
//-----------------------Follow Datasheet instructions--------------------------
void lcd_init(void)
{
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  // or you can use a loop to set all data pins at once:
  // for(uint8_t i = 0; i < 8; i++)
  // {
  //   pinMode(data_pins[i], OUTPUT); // Set all data pins to LOW initially
  // }

  lcd_command(home);
  lcd_command(function_set8);   
  lcd_command(display_on);      
  lcd_command(auto_increment);
}
//------------------------------------------------------------------------------
void lcd_command(uint8_t command)
{
  digitalWrite(RS, LOW);          // RS = 0;     //  Instruction register ( commands ).
  lcd_sendBits(command);
}
//------------------------------------------------------------------------------
void lcd_data(uint8_t data)
{
  digitalWrite(RS, HIGH);         // RS = 1;     //  Data register  ( strings and characters ).
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
  /*  
  // This is the original way to set data pins individually.
  // It is less efficient than using a loop, but it is shown here for clarity.
  // Set data pins according to the data bits.
  // This assumes that the data is sent in LSBFIRST order.
  // If you want to use MSBFIRST, you can change the getBit function accordingly. Both methods are shown in the comments below.
  digitalWrite(D0, getBit(0, data, LSBFIRST));   
  digitalWrite(D1, getBit(1, data, LSBFIRST));   
  digitalWrite(D2, getBit(2, data, LSBFIRST));   
  digitalWrite(D3, getBit(3, data, LSBFIRST));  

  digitalWrite(D4, getBit(4, data, LSBFIRST));   
  digitalWrite(D5, getBit(5, data, LSBFIRST));   
  digitalWrite(D6, getBit(6, data, LSBFIRST));   
  digitalWrite(D7, getBit(7, data, LSBFIRST)); 
  */  
  

  // This is an alternative way to set data pins individually.
  // It uses MSBFIRST order, which is the most common way to send data.
  // Alternatively, you can use MSBFIRST if needed.
  digitalWrite(D0, getBit(0, data, MSBFIRST));   
  digitalWrite(D1, getBit(1, data, MSBFIRST));   
  digitalWrite(D2, getBit(2, data, MSBFIRST));   
  digitalWrite(D3, getBit(3, data, MSBFIRST));  

  digitalWrite(D4, getBit(4, data, MSBFIRST));
  digitalWrite(D5, getBit(5, data, MSBFIRST));   
  digitalWrite(D6, getBit(6, data, MSBFIRST));   
  digitalWrite(D7, getBit(7, data, MSBFIRST)); 
  
  // or you can use a loop to set all data pins at once:
  // This is more efficient and cleaner.
  // here we assume that data_pins[] is an array containing the pin numbers for D0 to D7.
  // Make sure to define data_pins[] in lcd8.h as shown in the original snippet.
  // This will set the data pins according to the bits in the data variable.
  /*
  for(uint8_t i = 0; i < 8; i++)
	{
    // Set each data pin according to the corresponding bit in the data.
    digitalWrite(data_pins[i], getBit(i, data, MSBFIRST));
	}
  */

  // Latch the data to the LCD.
  // This is done by toggling the EN pin.
  latch();
}
//------------------------------------------------------------------------------
uint8_t getBit(uint8_t pos , uint8_t data, uint8_t dir = LSBFIRST)
{ 
  uint8_t pbit = LOW;
  
  switch(dir)
  {
    case(LSBFIRST): pbit = (data & (0x01 << pos)) ? HIGH : LOW; break;      // LSB first
    case(MSBFIRST): pbit = (data & (0x80 >> (7-pos))) ? HIGH : LOW; break;  // MSB first		
  }

  return pbit;
}
//------------------------------------------------------------------------------
void latch(void)
{
  digitalWrite(EN, HIGH);   // EN  = 1;
  delay(5);
  digitalWrite(EN, LOW);    // EN = 0;
}
//------------------------------------------------------------------------------
#endif