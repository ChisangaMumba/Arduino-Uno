#ifndef LM75_C
#define	LM75_C
//------------------------------------------------------------------------------
#include "LM75.h"
//------------------------------------------------------------------------------
void LM75_init()
{  
  //For Thermostat functions ONLY... can be left out if so wished and device will still read Tempr
  LM75_set(TOS_ADDRESS, 0x2380);     //Over Temperature Threshold Activate - I set it to 35.50C
  LM75_set(THYST_ADDRESS, 0x1E80);   //Over Temperature Threshold deactivate - I set it to 30.50C
}
//------------------------------------------------------------------------------
float LM75_read(uint8_t regAddress)
{
  int16_t data[2];
  
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS + 0);        // 0 = Write             
  I2C_write(regAddress);        
  I2C_restart();                           
  I2C_write(LM75_ADDRESS + 1);        // 1 = Read   
  data[0] = I2C_read(ACK);
  data[1] = I2C_read(NACK);
	
  I2C_stop();
  
  return toFloat((data[0] << 8) + data[1]);
}
//------------------------------------------------------------------------------
void LM75_setConfig(uint8_t data)
{  
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS);                       
  I2C_write(CONFIGURATION_ADDRESS);              
  I2C_write(data);       
  
  I2C_stop();
}
//------------------------------------------------------------------------------
uint8_t LM75_readConfig()
{  
	uint8_t config;
	
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS + 0);        // 0 = Write               
  I2C_write(CONFIGURATION_ADDRESS);        
  I2C_restart();                           
  I2C_write(LM75_ADDRESS + 1);        // 1 = Read   
  config = I2C_read(NACK);
	
  I2C_stop();
  
  return config;
}
//------------------------------------------------------------------------------
void LM75_set(uint8_t regAddress, int16_t data)
{  
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS);                    
  I2C_write(regAddress);      	//Registers: Config,THYST,OVER TEMP SINK (OS) /*See Datasheet*/                       
  I2C_write(data>>8);         	//MSByte       
  I2C_write(data);            	//LSByte
  
  I2C_stop();
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
  float result = (float)(tempr >> 8);      //Discard LSByte (Only holds fraction flag bit - see datasheet)
              
  return (tempr & FRACTION_FLAG) ? (result + 0.5) : result;
}
//------------------------------------------------------------------------------
#endif