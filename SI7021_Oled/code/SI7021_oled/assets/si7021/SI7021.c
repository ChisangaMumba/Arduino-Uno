#ifndef SI7021_H
#define	SI7021_H
//------------------------------------------------------------------------------
#include "SI7021.h"
//------------------------------------------------------------------------------
void SI7021_init(uint8_t res)
{	
	I2C_init(); 
	
	SI7021_command(RESET_CMD);
	delay(30);
	SI7021_writeConfig(res);
}
//------------------------------------------------------------------------------
uint8_t SI7021_readConfig(void)
{
	uint8_t data_ = 0;

	I2C_start(); 

	I2C_write((SI7021_ADDR << 1) | 0);  // 0 = Write  
	I2C_write(READ_CONFIG_CMD);
	I2C_restart();
	I2C_write((SI7021_ADDR << 1) | 1);  // 1 = Read 	
	data_ = I2C_read(NACK);						

	I2C_stop();

	return data_;
}
//------------------------------------------------------------------------------
void SI7021_writeConfig(uint8_t data_)
{	
	uint8_t config = SI7021_readConfig();

	I2C_start(); 

	I2C_write((SI7021_ADDR << 1) | 0);  // 0 = Write  
	I2C_write(WRITE_CONFIG_CMD);						
	I2C_write(data_ | config);

	I2C_stop();
}
//------------------------------------------------------------------------------
void SI7021_command(uint8_t command)
{
	I2C_start();                      

	I2C_write((SI7021_ADDR << 1) | 0);  // 0 = Write             
	I2C_write(command);

	I2C_stop(); 
}
//------------------------------------------------------------------------------
uint16_t SI7021_readConv(uint8_t command)
{
	uint8_t data_[2] = {0, 0}; 

	SI7021_command(command);
	delay(30);				
		
	I2C_start();

	I2C_write((SI7021_ADDR << 1) | 1);  // 1 = Read 	
	data_[1] = I2C_read(ACK);						// MSB
	data_[0] = I2C_read(NACK);					// LSB

	I2C_stop();

	return (data_[1] << 8) + data_[0];
}
//------------------------------------------------------------------------------
float SI7021_getHumd()
{
	uint16_t rawHumd = SI7021_readConv(HUMD_NO_HOLD_CMD);

	return ( ((float)rawHumd *125) / 65536 ) - 6;
}
//------------------------------------------------------------------------------
float SI7021_getTemp()
{
	uint16_t rawTemp = SI7021_readConv(TEMP_NO_HOLD_CMD);

	return ( ((float)rawTemp * 175.72f)/ 65536) - 46.85f;
}
//------------------------------------------------------------------------------
#endif