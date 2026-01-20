#ifndef LM75_C
#define	LM75_C
//------------------------------------------------------------------------------
#include "lm75.h"
//------------------------------------------------------------------------------
void lm75_init(int16_t tempH, int16_t tempL)
{ 
	I2C_init(); 
	
	//For Thermostat functions ONLY... can be left out if so wished and device will still read Tempr
	lm75_set(TOS_REG,  tempH << 8);			//Over Temperature Threshold Activate 
	lm75_set(THYST_REG,tempL << 8);			//Over Temperature Threshold deactivate
}
//------------------------------------------------------------------------------
int16_t lm75_read(uint8_t regAddress)
{
  uint8_t data_[2];
  
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS + 0);        // 0 = Write             
  I2C_write(regAddress);        
  I2C_restart();                           
  I2C_write(LM75_ADDRESS + 1);        // 1 = Read   
  data_[1] = I2C_read(ACK);						// MSB
  data_[0] = I2C_read(NACK);					// LSB
	
  I2C_stop();
  
	return (data_[1] << 8) + data_[0];
}
//------------------------------------------------------------------------------
void lm75_setConfig(uint8_t data_)
{  
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS);                       
  I2C_write(CONFIG_REG);              
  I2C_write(data_);       
  
  I2C_stop();
}
//------------------------------------------------------------------------------
uint8_t lm75_readConfig()
{  
	uint8_t config;
	
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS + 0);        // 0 = Write               
  I2C_write(CONFIG_REG);        
  I2C_restart();                           
  I2C_write(LM75_ADDRESS + 1);        // 1 = Read   
  config = I2C_read(NACK);
	
  I2C_stop();
  
  return config;
}
//------------------------------------------------------------------------------
void lm75_set(uint8_t regAddress, int16_t data_)
{  
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS);                    
  I2C_write(regAddress);      	//Registers: Config,THYST,OVER TEMP SINK (OS) /*See Datasheet*/                       
  I2C_write(data_ >> 8);        //MSByte       
  I2C_write(data_);            	//LSByte
  
  I2C_stop();
}
//------------------------------------------------------------------------------
float lm75_getTemp(uint8_t regAddress)
{
	int16_t tempr = lm75_read(regAddress);
	
	return toFloat(tempr);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
  float  result = (float)(tempr >> 8);      //Discard LSByte (Only holds fraction flag bit - see datasheet)  
	
	return (tempr & FRACTION_FLAG) ? result + 0.5 : result;
}
//------------------------------------------------------------------------------
#endif