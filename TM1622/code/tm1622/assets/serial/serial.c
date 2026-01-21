#ifndef SERIAL_C
#define SERIAL_C
//-----------------------------------------------------------------------------------
#include "serial.h"
//-----------------------------------------------------------------------------------
void serialInit(void)
{
  pinMode(CS,   OUTPUT);
  pinMode(WR,   OUTPUT); 
  pinMode(DATA, OUTPUT);
}
//-----------------------------------------------------------------------------------
// Send up to 16 bits, MSB or LSB
//-----------------------------------------------------------------------------------
void serialOut(uint8_t dir, uint8_t sdata, uint8_t noBits)
{
  // Data is shifted out bitwise, either LSB-first or MSB-first.
  // The mask is used to isolate the bit being transmitted.

  pinMode(DATA, OUTPUT); 
  uint8_t mask = (dir == LSBFIRST) ? 0x01 : 0x01 << (noBits - 1);
  
  for(uint8_t tx = 0; tx < noBits; tx++)
  {
    digitalWrite(WR, LOW);			// WR = 0;

    switch(dir)
    {
      case(0): digitalWrite(DATA, ((sdata >> tx) & mask) ? HIGH : LOW); break; // LSB first
      case(1): digitalWrite(DATA, ((sdata << tx) & mask) ? HIGH : LOW); break; // MSB first		
    }
    
    digitalWrite(WR, HIGH);			// WR = 1;
  }
}
//-----------------------------------------------------------------------------------
uint8_t serialIn(uint8_t dir)
{
  uint8_t sdata = 0;
  
  for(uint8_t Rx = 0; Rx < 8; Rx++)
  {
    digitalWrite(WR, LOW);			// WR = 0;

    switch(dir)
    {
      case(0): sdata += digitalRead(DATA) <<    Rx;  break;  // LSB first
      case(1): sdata += digitalRead(DATA) << (7-Rx); break;  // MSB first		
    }
    
    digitalWrite(WR, HIGH);			// WR = 1;
  }
  
  return sdata;
}
//-----------------------------------------------------------------------------------
#endif