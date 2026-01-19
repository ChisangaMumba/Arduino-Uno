#ifndef EXPANDER_H
#define EXPANDER_H
//------------------------------------------------------------------------------
#include "MCP23S17.h"
uint8_t CS1  = 10;
//------------------------------------------------------------------------------
void EXPANDER_init(uint8_t portA, uint8_t portB)
{
  pinMode(CS1, OUTPUT);
  
  SPI_init();   
  EXPANDER_write(IODIRA, portA);       
  EXPANDER_write(IODIRA, portA);
  EXPANDER_write(IODIRB, portB);
}
//------------------------------------------------------------------------------
void EXPANDER_write(uint8_t portAddr, uint8_t data)
{
  digitalWrite(CS1, LOW);          // CS1 = 0;  //Chip Select: active low

  SPI_write(WRITE);
  SPI_write(portAddr);
  SPI_write(data);
  
  digitalWrite(CS1, HIGH);         // CS1 = 1;
}
//------------------------------------------------------------------------------
uint8_t EXPANDER_read(uint8_t portAddr)
{
	uint8_t data = 0;
	
  digitalWrite(CS1, LOW);           //  CS1 = 0;
  
  SPI_write(READ);
  SPI_write(portAddr);
  data = SPI_read();
  
  digitalWrite(CS1, HIGH);          //  CS1 = 1;

  return data;
}
//------------------------------------------------------------------------------
#endif