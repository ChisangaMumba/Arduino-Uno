#ifndef LCD_Serial_H
#define LCD_Serial_H
//------------------------------------------------------------------------------
#include "LCD_Serial_Prototypes.h"
#include "../pcf8574/pcf8574.h"
//------------------------------------------------------------------------------
void LCD_init(char address)
{
  I2C_init();    
  Expander_init(address);
  
  LCD_command(home);
  LCD_command(function_set4);
  LCD_command(display_on);
  LCD_command(clear); 
}
//------------------------------------------------------------------------------
void LCD_data(char data)
{
  RS = 1;                        //Data register  ( Strings and characters ).
  LCD_transmit(data); 
}
//------------------------------------------------------------------------------
void LCD_command(char command)
{
  RS = 0;                        //Instruction register ( commands ).
  LCD_transmit(command); 
}
//------------------------------------------------------------------------------
void LCD_transmit(char data)
{
  LCD_sendNibble(data & 0xF0);     //Higher Nibble
  LCD_sendNibble(data << 4);       //Lower Nibble
}
//------------------------------------------------------------------------------
void LCD_string(char row, char col, char * text)
{
  LCD_command(RowAddr[row] + col);  
  while(*text)
  {
    uint8_t chr = *text++;
		
		if(chr == 176)    // 176 is ° in Extended ascii
			chr = 0xDF;     //223d is the value of ° symbol in Hitachi HD44780 LCDs
		
		if(chr != 194)	  //° is implicitly split into 194 and 176 by the arduino c++ compiler
      LCD_data(chr);
  }
}
//------------------------------------------------------------------------------
void LCD_sendNibble(char data)
{
  data = data | RS;
	
  //Enable is pulsed to latch the data
  Expander_write(data | EN_high);
  delay(5);
  Expander_write(data & EN_low);
}
//------------------------------------------------------------------------------
#endif