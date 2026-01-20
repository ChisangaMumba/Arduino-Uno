#ifndef TH02_C
#define	TH02_C
//------------------------------------------------------------------------------
#include "th02.h"
//------------------------------------------------------------------------------
void TH02_init(void)
{
	I2C_init(); 
}
//------------------------------------------------------------------------------
void TH02_command(uint8_t command)
{
	I2C_start();                      

	I2C_write((TH02_ADDR << 1) | 0);  // 0 = Write             
	I2C_write(CONFIG_REG);
	I2C_write(command);

	I2C_stop();

	// Wait for the sensor to complete measurement (adjust delay as necessary).
	delay(40);				//  35ms max in Normal mode, 18ms max in Fast mode
}
//------------------------------------------------------------------------------
uint8_t TH02_readDevice(uint8_t command)
{
	uint8_t data_ = 0;

	I2C_start(); 

	I2C_write((TH02_ADDR << 1) | 0);  // 0 = Write  
	I2C_write(command);
	I2C_restart();
	I2C_write((TH02_ADDR << 1) | 1);  // 1 = Read 	
	data_ = I2C_read(NACK);						

	I2C_stop();

	return data_;
}
//------------------------------------------------------------------------------
uint16_t TH02_readConv(uint8_t command)
{
	uint8_t data_[2] = {0, 0}; 

	TH02_command(command);

	I2C_start(); 

	I2C_write((TH02_ADDR << 1) | 0);  // 0 = Write  
	I2C_write(0x01);
	I2C_restart();
	I2C_write((TH02_ADDR << 1) | 1);  // 1 = Read 	
	data_[1] = I2C_read(ACK);					// MSB
	data_[0] = I2C_read(NACK);				// LSB

	I2C_stop();

	return (data_[1] << 8) + data_[0];
}
//------------------------------------------------------------------------------
float TH02_getHumd()
{
	uint16_t rawHumd = TH02_readConv(HUMD_CMD) >> 4;

	return ((float)rawHumd / 16.0f) - 24.0f;
}
//------------------------------------------------------------------------------
float TH02_getTemp()
{
	uint16_t rawTemp = TH02_readConv(TEMP_CMD) >> 2;
	
	return ((float)rawTemp / 32.0f) - 50.0f;
}
//------------------------------------------------------------------------------
#endif