#ifndef LCD4_C
#define	LCD4_C
//------------------------------------------------------------------------------
#include "lcd4.h"
//-----------------------Follow Datasheet instructions--------------------------
void LCD_init()
{
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);

  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  LCD_command(home);
  LCD_command(function_set4);   
  LCD_command(display_on);      
  LCD_command(auto_increment);
}
//------------------------------------------------------------------------------
void LCD_command(uint8_t command)
{
  digitalWrite(RS, LOW);          //  RS = 0;     //  Instruction register ( commands ).
  LCD_transmit(command);
}
//------------------------------------------------------------------------------
void LCD_data(uint8_t data)
{
  digitalWrite(RS, HIGH);         //  RS = 1;     //  Data register  ( strings and characters ).
  LCD_transmit(data);
}
//------------------------------------------------------------------------------
void LCD_string(uint8_t row, uint8_t column, uint8_t text[])
{
  LCD_command(rowAddr[row] + column);  // Set coordinates.

  for(uint8_t i = 0; text[i]; i++)
  {
    LCD_data(text[i]);
  }
}
//------------------------------------------------------------------------------
void LCD_transmit(uint8_t data)
{
  uint8_t pinBits[8];
   
  LCD_getBits(pinBits, data);
  LCD_sendBits(pinBits);
}
//------------------------------------------------------------------------------
void LCD_sendBits(uint8_t pinBit[])
{
  //Higher Nibble
  digitalWrite(D4, pinBit[4]);   //  D4 = pinBit[4];
  digitalWrite(D5, pinBit[5]);   //  D5 = pinBit[5];
  digitalWrite(D6, pinBit[6]);   //  D6 = pinBit[6];
  digitalWrite(D7, pinBit[7]);   //  D7 = pinBit[7];
  latch();
  
  //Lower Nibble
  digitalWrite(D4, pinBit[0]);   //  D4 = pinBit[0];
  digitalWrite(D5, pinBit[1]);   //  D5 = pinBit[1];
  digitalWrite(D6, pinBit[2]);   //  D6 = pinBit[2];
  digitalWrite(D7, pinBit[3]);   //  D7 = pinBit[3];
  latch();
}
//------------------------------------------------------------------------------
void LCD_getBits(uint8_t pinBit[], uint8_t data)
{ 
  for(uint8_t i = 0; i < 8; i++)
  {
    pinBit[i] = ((data >> i) & 0x01) ? HIGH : LOW;
  }
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