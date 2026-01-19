#ifndef LCD_Serial_C
#define LCD_Serial_C
//------------------------------------------------------------------------------
#include "LCD_Serial.h"
uint8_t CS1  = 9;
//------------------------------------------------------------------------------
void LCD_init()
{
	SPI_init();

  pinMode(CS1, OUTPUT);
	digitalWrite(CS1, HIGH);       //CS1 = 1		//Deselect initially
  
  LCD_command(home);
  LCD_command(function_set4);
  LCD_command(display_on);
  LCD_command(clear); 
}
//------------------------------------------------------------------------------
void LCD_data(uint8_t data)
{
  RS = 1;                        //Data register_  ( Strings and characters ).
  
  LCD_transmit(data); 
}
//------------------------------------------------------------------------------
void LCD_command(uint8_t command)
{
  RS = 0;                        //Instruction register_ ( commands ).
  
  LCD_transmit(command); 
}
//------------------------------------------------------------------------------
void LCD_string(uint8_t row, uint8_t col, uint8_t text[])
{
  LCD_command(RowAddr[row] + col);  
  
  while(*text)
  {
    writeChar(*text++);
  }
}
//------------------------------------------------------------------------------
void LCD_transmit(uint8_t data)
{
	LCD_sendNibble(data & 0xF0);     //Higher Nibble
  LCD_sendNibble(data << 4);       //Lower Nibble
}
//------------------------------------------------------------------------------
void LCD_sendNibble(uint8_t data)
{
  data = data | RS;
	
  ShiftReg_write(data | EN_high);
  delay(5);
  ShiftReg_write(data & EN_low);
}
//------------------------------------------------------------------------------
void ShiftReg_write(uint8_t data)
{
  digitalWrite(CS1, LOW);        //CS1 = 0
  SPI_write(data);
  digitalWrite(CS1, HIGH);       //CS1 = 1
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr)
{
  if(chr == 176)    // 176 is ° in Extended ascii
    chr = 0xDF;     //223d is the value of ° symbol in Hitachi HD44780 LCDs
  
  if(chr != 194)	  //° is implicitly split into 194 and 176 by the arduino c++ compiler
    LCD_data(chr);
}
//------------------------------------------------------------------------------
#endif