#ifndef TCN75_C
#define	TCN75_C
//------------------------------------------------------------------------------
#include "tcn75.h"
//------------------------------------------------------------------------------
void tcn75_init(int16_t tempH, int16_t tempL, uint8_t res)
{ 
	i2c_init(); 
	
	//For Thermostat functions ONLY... can be left out if so wished and device will still read Tempr
	tcn75_set(TOS_REG,  tempH << 8);			// Over Temperature Threshold Activate 
	tcn75_set(THYST_REG,tempL << 8);			// Over Temperature Threshold deactivate
	
	tcn75_setConfig(res);
	RES_INDEX = (tcn75_readConfig() & 0x60) >> 5;	// get resolution
}
//------------------------------------------------------------------------------
int16_t tcn75_read(uint8_t regAddress)
{
	uint8_t data_[2];
	
	i2c_start();                      
	
	i2c_write(TCN75_ADDRESS + 0);        	// 0 = Write             
	i2c_write(regAddress);        
	i2c_restart();                           
	i2c_write(TCN75_ADDRESS + 1);        	// 1 = Read   
	data_[1] = i2c_read(ACK);							// MSB
	data_[0] = i2c_read(NACK);						// LSB
	
	i2c_stop();
	
	return (data_[1] << 8) + data_[0];
}
//------------------------------------------------------------------------------
void tcn75_setConfig(uint8_t data_)
{ 
	uint8_t config = tcn75_readConfig();
	
	i2c_start();                      
	
	i2c_write(TCN75_ADDRESS);                       
	i2c_write(CONFIG_REG);              
	i2c_write(data_ | config);       
	
	i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t tcn75_readConfig()
{  
	uint8_t config;
	
	i2c_start();                      
	
	i2c_write(TCN75_ADDRESS + 0);        // 0 = Write               
	i2c_write(CONFIG_REG);        
	i2c_restart();                           
	i2c_write(TCN75_ADDRESS + 1);        // 1 = Read   
	config = i2c_read(NACK);
	
	i2c_stop();
	
	return config;
}
//------------------------------------------------------------------------------
void tcn75_set(uint8_t regAddress, int16_t data_)
{  	
	i2c_start();                      
	
	i2c_write(TCN75_ADDRESS);                    
	i2c_write(regAddress);      	// Registers: Config,THYST,OVER TEMP SINK (OS) /*See Datasheet*/                       
	i2c_write(data_ >> 8);        // MSByte       
	i2c_write(data_);            	// LSByte
	
	i2c_stop();
}
//------------------------------------------------------------------------------
float tcn75_getTemp(uint8_t regAddress)
{
	int16_t tempr = tcn75_read(regAddress);
	
	return toFloat(tempr, RES_INDEX);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr, uint8_t resInd)
{
	float  result = (float)(tempr >> 8);								// Discard LSByte (Only holds fraction flag bit - see datasheet)  
	uint8_t count = (tempr & FRAC_FLAG) >> 4;          

	if(count) 
	{
		result += ((count >> (3-resInd)) * resValues[resInd]);
	}

	return result;
}
//------------------------------------------------------------------------------
#endif