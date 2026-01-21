#ifndef MAX7219_C
#define	MAX7219_C
//------------------------Dot Matrix LED  Driver--------------------------------
#include "max7219.h"
//------------------------------------------------------------------------------
void max7219_init(uint8_t noChips)
{
  SPI.begin();
  
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);   // CS1 = 1 (unselect initially)

  while(noChips)
      max7219_config(--noChips);
}
//------------------------------------------------------------------------------
void max7219_config(uint8_t chip)
{
  max7219_write(DECODE_MODE_REG,DISABLE_DECODE,chip);    
  max7219_write(INTESITY_REG,BRIGHTNESS,chip);     
  max7219_write(SCAN_LIMIT_REG,SCAN_ALL_DIGITS,chip);     
  max7219_write(SHUTDOWN_REG,NORMAL_OPERATION,chip);
  max7219_write(DISPLAY_TEST_REG,DISABLE_TEST,chip);   
}
//------------------------------------------------------------------------------
void max7219_write(uint8_t regName, uint8_t data, uint8_t chip)
{
  digitalWrite(CS, LOW);      //CS = 0

  SPI.transfer(regName);
  SPI.transfer(data);
  while(chip--)
      max7219_NoOperation();  //Used for daisy chained (Cascaded) arrangements
  
  digitalWrite(CS, HIGH);     //CS = 1
}
//------------------------------------------------------------------------------
void max7219_displayText(uint8_t * text)
{ 
  uint8_t chip = 0;
 
  while(*text)
  { 
    writeChar(*text++, chip); 
  }
}
//----------Passes the data to the adjacent max7219 in the Daisy Chain---------
void max7219_NoOperation(void)
{
  SPI.transfer(NO_OP_REG);
  SPI.transfer(0x00);      //Don't care (Can be any arbitrary value)  
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr, uint8_t & chip)
{
  uint8_t row, col; 

  for(col = 0; col < 5; col++)
  {
    if(isprint(chr) && chr != '.' && chr != 194) // If the character is printable and not a decimal point or degree symbol
    {
      row = chr - ' '; // (Text-32)...because the first 32 ASCII character codes are none Printable (control chars)
      max7219_write(col+1, chars[row][col], chip);
    }
    else
        if(chr == 176) // If the character is a degree symbol (°)
        {
          // ° is implicitly split into 194 and 176 by the arduino c++ compiler
          max7219_write(7, custom_char[0][3], chip-1);
          max7219_write(8, custom_char[0][4], chip-1);
        }
  }

  displayDp(chr, chip);   // Display decimal point if needed
} 
//------------------------------------------------------------------------------
// The decimal point is represented by 0x60 in the 7th and 8th columns
// of the MAX7219, which corresponds to the decimal point position.
//------------------------------------------------------------------------------
void displayDp(uint8_t chr, uint8_t & chip)
{
  if(chr == '.')
  { 
    max7219_write(7, 0x60, chip-1);
    max7219_write(8, 0x60, chip-1);
  }

  if(isprint(chr) && chr != '.' && (chr != 176 || chr != 194))
    chip++;
}
//------------------------------------------------------------------------------
#endif		