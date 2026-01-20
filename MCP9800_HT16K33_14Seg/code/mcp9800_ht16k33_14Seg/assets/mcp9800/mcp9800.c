#ifndef mcp9800_C
#define mcp9800_C
//------------------------------------------------------------------------------
#include "mcp9800.h"
//------------------------------------------------------------------------------
void mcp9800_init(uint8_t addr, uint8_t res)
{
	delay(10);
	mcp9800_writeConfig(addr, res);
}
//------------------------------------------------------------------------------
void mcp9800_writeConfig(uint8_t addr, uint8_t settings)
{
	I2C_start(); 
    
  I2C_write( addr + Wr ); 
  I2C_write( CONFIG_REG ); 
  I2C_write( settings );       
                           
  I2C_stop();
}
//------------------------------------------------------------------------------
uint8_t mcp9800_readConfig(uint8_t addr)
{
	 uint8_t config = 0;
	
   I2C_start();
    
   I2C_write( addr + Wr );
	I2C_write( CONFIG_REG );
	I2C_restart();	
   I2C_write( addr + Rd );	        
   config = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop(); 
	
	 return config;
}
//------------------------------------------------------------------------------
uint8_t mcp9800_getResolutionNum(uint8_t addr)
{
  uint8_t resNum = mcp9800_readConfig(addr);
  
  return (resNum & 0x60) >> 5;
}
//------------------------------------------------------------------------------
void mcp9800_write(uint8_t addr, uint8_t reg, unsigned int settings)
{
  I2C_start(); 
    
  I2C_write( addr + Wr ); 
  I2C_write( reg ); 
  I2C_write( settings >> 8);
  I2C_write( settings & 0x00ff);
                           
  I2C_stop();
}
//------------------------------------------------------------------------------
int16_t mcp9800_read(uint8_t addr, uint8_t reg)
{
	uint8_t data[2];
   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( reg );	    
   I2C_restart();	
   I2C_write( addr + Rd );	    
   data[1] = I2C_read(ACK);     
   data[0] = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return ( (data[1] << 8) + data[0] );   //NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
float mcp9800_getTemperature(uint8_t addr)
{
   int16_t rawtemp = mcp9800_read(addr, TEMP_REG);
   uint8_t resNum = mcp9800_getResolutionNum(addr);

   return calcTemp(rawtemp, resNum);
}
//------------------------------------------------------------------------------
float calcTemp(int16_t rawData, uint8_t resInd)
{
  float tempr = (rawData >> 8);     
  int16_t count = rawData & 0x00F0;          
  
  if(count) 
  {
		tempr += ((count >> (7-resInd)) * resValues[resInd]);
  }
  
	return tempr; 
}
//------------------------------------------------------------------------------
#endif