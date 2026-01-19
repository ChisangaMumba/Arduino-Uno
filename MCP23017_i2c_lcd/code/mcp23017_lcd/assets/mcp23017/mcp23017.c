#ifndef EXPANDER_H
#define EXPANDER_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
#include "MCP23017.h"
//------------------------------------------------------------------------------
void EXPANDER_init(uint8_t portA, uint8_t portB)
{
  I2C_init();          
  
  EXPANDER_write(IODIRA, portA);
  EXPANDER_write(IODIRB, portB);
}
//------------------------------------------------------------------------------
void EXPANDER_write(uint8_t portAddr, uint8_t data)
{
  I2C_start();
  I2C_write(WRITE);
  I2C_write(portAddr);
  I2C_write(data);
  I2C_stop();
}
//------------------------------------------------------------------------------
uint8_t EXPANDER_read(uint8_t portAddr)
{
	uint8_t data;
	
  I2C_start();
  
  I2C_write(WRITE);
  I2C_write(portAddr);
  I2C_restart();
  I2C_write(READ);
  data = I2C_read(1);
  
  I2C_stop();

  return data;
}
//------------------------------------------------------------------------------
#endif