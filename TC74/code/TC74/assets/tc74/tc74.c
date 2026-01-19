#ifndef TC74_C
#define	TC74_C
//------------------------------------------------------------------------------
#include "TC74.h"
//------------------------------------------------------------------------------
void TC74_init(uint8_t data)
{
  I2C_init();
	TC74_config(data);
}
//------------------------------------------------------------------------------
void TC74_config(uint8_t data)
{
  I2C_start();                      
  
  I2C_write(READ);								//Datasheet says WRITE (0x9B), but that does NOT work              
  I2C_write(CONFIG_REG);                                      
  I2C_write(data);                
  
  I2C_stop();
}
//------------------------------------------------------------------------------
int8_t TC74_read(uint8_t regAddress)
{
	int8_t result = 0;
	
  I2C_start();                      
  
  I2C_write(READ);								//Datasheet says WRITE (0x9B), but that does NOT work 
  I2C_write(regAddress);           
  I2C_restart();                           
  I2C_write(WRITE);								//Datasheet says READ (0x9A), but that does NOT work                 
	result = I2C_read(NACK);
  
  I2C_stop();
  
  return result;
}
//------------------------------------------------------------------------------
#endif