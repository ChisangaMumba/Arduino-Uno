#ifndef mcp9800_C
#define mcp9800_C
//------------------------------------------------------------------------------
#include "mcp9800.h"
//------------------------------------------------------------------------------
void mcp9800_init(int16_t highTemp, int16_t lowTemp, uint8_t res)
{
	delay(10);
	
  mcp9800_write(TSET_REG,  highTemp << 8);    // Set the temperature set register to default
  mcp9800_write(THYST_REG, lowTemp  << 8);    // Set the hysteresis register to default
  mcp9800_setConfig(res);
  resNum = mcp9800_getResNum();               // Store the resolution number
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
  i2c_write(settings >> 8);          // MSByte first
  i2c_write(settings & 0x00ff);      // LSByte second
                           
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
  data[1] = i2c_read(ACK);     // MSB
  data[0] = i2c_read(NACK);    // LSB. Signal End of reception with NACK

  i2c_stop();	
  
  return ((data[1] << 8) + data[0]);   // NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
float mcp9800_getTemp(uint8_t reg = TEMP_REG)
{
  convDelay(resNum);  // Wait for conversion to complete based on resolution
  int16_t rawtemp = mcp9800_read(reg);

  return toFloat(rawtemp);
}
//------------------------------------------------------------------------------
float toFloat(int16_t rawData)
{
  float tempr   = rawData >> 8;         // Get the integer part
  int16_t count = rawData & FRAC_FLAG;          
  
  if(count) 
  {
		tempr += ((count >> 4) * 0.0625);   // Get the fractional part
  }
  
	return tempr; 
}
//------------------------------------------------------------------------------
void convDelay(uint8_t resNum)
{
  switch(resNum)
  {
    case (0x00): delay(75);  break;   // 0.5°C
    case (0x01): delay(150); break;   // 0.25°C
    case (0x02): delay(300); break;   // 0.125°C
    case (0x03): delay(600); break;   // 0.0625°C
    default:     delay(75);  break;   // 0.5°C
  }
  // Delay based on resolution to allow temperature conversion to complete
  // 0.5°C: 75ms, 0.25°C: 150ms, 0.125°C: 300ms, 0.0625°C: 600ms
  // This ensures accurate temperature readings after writing to the device
}
//------------------------------------------------------------------------------
#endif