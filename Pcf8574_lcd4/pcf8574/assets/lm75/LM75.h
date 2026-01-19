#ifndef LM75_H
#define	LM75_H
//------------------------------------------------------------------------------
#include "LM75_Prototypes.h"
#include "../i2c.h"
//------------------------------------------------------------------------------
void LM75_init()
{  
  //For Thermostat functions ONLY... can be left out if so wished and device will still read Tempr
  LM75_set(TOS_ADDRESS,0x2380);     //Over Temperature Threshold Activate - I set it to 35.50C
  LM75_set(THYST_ADDRESS,0x1E80);   //Over Temperature Threshold deactivate - I set it to 30.50C
}
//------------------------------------------------------------------------------
float LM75_read(uint8_t regAddress)
{
  uint8_t MSB, LSB;
  
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS + 0);        // 0 = Write             
  I2C_write(regAddress);        
  I2C_restart();                           
  I2C_write(LM75_ADDRESS + 1);        // 1 = Read   
  MSB = I2C_read(ACK);
  LSB = I2C_read(NACK);
	
  I2C_stop();
  
  return toFloat((MSB << 8) + LSB);
}
//------------------------------------------------------------------------------
void LM75_setConfig(uint8_t _data)
{  
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS);                       
  I2C_write(CONFIGURATION_ADDRESS);              
  I2C_write(_data);       
  
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
void LM75_set(uint8_t regAddress, signed int _data)
{  
  I2C_start();                      
  
  I2C_write(LM75_ADDRESS);                    
  I2C_write(regAddress);      	//Registers: Config,THYST,OVER TEMP SINK (OS) /*See Datasheet*/                       
  I2C_write(_data>>8);         	//MSByte       
  I2C_write(_data);            	//LSByte
  
  I2C_stop();
}
//------------------------------------------------------------------------------
float toFloat(signed int tempr)
{
  float result = (float)(tempr>>8);      //Discard LSByte (Only holds fraction flag bit - see datasheet)
  int isfraction = tempr & FRACTION_FLAG;          
  
  if(isfraction) 
  {
    result += 0.5;
  }
  
  return (result);
}
//------------------------------------------------------------------------------
#endif