#ifndef mcp9800_C
#define mcp9800_C
//------------------------------------------------------------------------------
#include "mcp9800.h"
//------------------------------------------------------------------------------
void mcp9800_init(uint8_t res)
{
	delay(10);
	mcp9800_setConfig(res);
}
//------------------------------------------------------------------------------
void mcp9800_setConfig(uint8_t settings)
{
	i2c_start(); 
    
  i2c_write(ADDR + Wr); 
  i2c_write(CONFIG_REG); 
  i2c_write(settings);       
                           
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t mcp9800_getConfig(void)
{
	uint8_t config = 0;
	
  i2c_start();
    
  i2c_write(ADDR + Wr);
	i2c_write(CONFIG_REG);
	i2c_restart();	
  i2c_write(ADDR + Rd);	        
  config = i2c_read(NACK);    // Signal End of reception with NACK
	
  i2c_stop(); 
	
	return config;
}
//------------------------------------------------------------------------------
uint8_t mcp9800_getResNum(void)
{
  uint8_t resNum = mcp9800_getConfig();
  
  return (resNum & 0x60) >> 5;
}
//------------------------------------------------------------------------------
void mcp9800_write(uint8_t reg, unsigned int settings)
{
  i2c_start(); 
    
  i2c_write(ADDR + Wr); 
  i2c_write(reg); 
  i2c_write(settings >> 8);
  i2c_write(settings & 0x00ff);
                           
  i2c_stop();
}
//------------------------------------------------------------------------------
int16_t mcp9800_read(uint8_t reg)
{
	uint8_t data[2];
   
  i2c_start(); 	           
  
  i2c_write(ADDR + Wr);	    
  i2c_write(reg);	    
  i2c_restart();	
  i2c_write(ADDR + Rd);	    
  data[1] = i2c_read(ACK);     
  data[0] = i2c_read(NACK);    // Signal End of reception with NACK

  i2c_stop();	
  
  return ((data[1] << 8) + data[0]);   //NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
float mcp9800_getTemp(void)
{
  int16_t rawtemp = mcp9800_read(TEMP_REG);

  return toFloat(rawtemp);
}
//------------------------------------------------------------------------------
float toFloat(int16_t rawData)
{
  float tempr   = rawData >> 8;         // Get the integer part
  int16_t count = rawData & FRAC_FLAG;          
  
  if(count) 
  {
		tempr += ((count >> 4) * 0.0625); // Get the fractional part
  }
  
	return tempr; 
}
//------------------------------------------------------------------------------
#endif