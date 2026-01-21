#ifndef TM162x_C
#define TM162x_C
//-----------------------------------------------------------------------------------
#include "tm162x.h"
//-----------------------------------------------------------------------------------
void TM162x_init(void)
{
  serialInit();
  delay(50);

  TM162x_command(CMD_SYS_EN);		
  TM162x_command(CMD_RC_32K);		
  //TM162x_command(CMD_BIAS_COM);     // Only for HT1621 or TM1621
  TM162x_command(CMD_LCD_OFF);		
  TM162x_setDisplay(CLEAR);
  TM162x_command(CMD_LCD_ON);  // Should turn it back on	
  delay(1000);
}
//-----------------------------------------------------------------------------------
void TM162x_command(uint8_t command)
{
  digitalWrite(CS, LOW);
  
  serialOut(MSBFIRST,   0b100, 3);
  serialOut(MSBFIRST, command, 8);
  serialOut(MSBFIRST,       1, 1);
  
  digitalWrite(CS, HIGH);
}
//-----------------------------------------------------------------------------------
void TM162x_data(uint8_t addr, uint8_t sdata, uint8_t noBits)
{
  // Note: bits needs to be a multiple of 4 as data is in nibbles
  digitalWrite(CS, LOW);
  
  serialOut(MSBFIRST, 0b101, 3);
  serialOut(MSBFIRST,  addr, 6);
  serialOut(LSBFIRST, sdata, noBits);
  
  digitalWrite(CS, HIGH);
}
//-----------------------------------------------------------------------------------
void TM162x_setDisplay(uint8_t state)
{
  // TM1622 or HT1622 has 64 possible 4-bit addresses
  for(uint8_t i = 0; i < 64; i++)
  {
    TM162x_data(i, (state) ? 0x0F : 0x00, 4);
  }
}
//-----------------------------------------------------------------------------------
void TM162x_print(uint8_t text[])
{
  //                           39,   35,   31,   27,   23,   19,   15,   11,    7,    3 
  uint8_t nibbleAddr[10] = { 0x27, 0x23, 0x1F, 0x1B, 0x17, 0x13, 0x0F, 0x0B, 0x07, 0x03 };
  uint16_t chr, i = 0;

  while(text[i])
  {
    chr = text[i];

    if(chr != 194)  // ° is implicitly split into 194 and 176 by the arduino c++ compiler
      writeChar(nibbleAddr[i++], chr);
  }
}
//-----------------------------------------------------------------------------------
void writeChar(uint8_t nibbleAddr, uint8_t chr)
{
  const uint8_t noBits = 4; // size of nibble
  uint16_t digit = (isprint(chr)) ? font[chr - ' '] : font_custom[0];

  TM162x_data(nibbleAddr - 0, digit >>  0, noBits);
  TM162x_data(nibbleAddr - 1, digit >>  4, noBits);
  TM162x_data(nibbleAddr - 2, digit >>  8, noBits);
  TM162x_data(nibbleAddr - 3, digit >> 12, noBits);
}
//-----------------------------------------------------------------------------------
#endif