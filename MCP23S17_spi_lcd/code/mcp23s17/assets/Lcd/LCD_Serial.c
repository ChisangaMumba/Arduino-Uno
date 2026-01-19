#ifndef LCD_SERIAL_C
#define LCD_SERIAL_C
//------------------------------------------------------------------------------
#include "LCD_Serial.h"
//------------------------------------------------------------------------------
void LCD_init()
{
  EXPANDER_init(0x00, 0x00);  //PortA & PortB all outputs
  
  LCD_command(home);
  LCD_command(function_set8);
  LCD_command(display_on);
  LCD_command(clear); 
}
//------------------------------------------------------------------------------
void LCD_data(uint8_t data)
{
  RS = 1;                        //Data register  ( Strings and characters ).
  LCD_transmit(data); 
}
//------------------------------------------------------------------------------
void LCD_command(uint8_t command)
{
  RS = 0;                        //Instruction register ( commands ).
  LCD_transmit(command); 
}
//------------------------------------------------------------------------------
void LCD_string(uint8_t row, uint8_t col, uint8_t text[])
{
  LCD_command(RowAddr[row] + col);  
  
  while(*text)
  {
    uint8_t chr = *text++;
		
		if(chr == 176)    //  176 is ° in Extended ascii
      chr = 0xDF;     //  223d is the value of ° symbol in Hitachi HD44780 LCDs
		
		if(chr != 194)	  //° is implicitly split into 194 and 176 by the arduino c++ compiler
      LCD_data(chr);
  }
}
//------------------------------------------------------------------------------
void LCD_transmit(uint8_t data)
{
  EXPANDER_write( OLATA, RS );
  EXPANDER_write( OLATB, data );
  
  LCD_latch();
}
//------------------------------------------------------------------------------
void LCD_latch()
{
  uint8_t data = 0x00 | RS;
  
  EXPANDER_write( OLATA, (data | EN_high) );   //Enable is pulsed to latch the data
  delay(5);
  EXPANDER_write( OLATA, (data & EN_low) );
}
//------------------------------------------------------------------------------
#endif