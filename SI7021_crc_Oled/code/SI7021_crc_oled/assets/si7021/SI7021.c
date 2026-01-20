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
	uint8_t data = 0;

	I2C_start(); 

	I2C_write((SI7021_ADDR << 1) | 0);  // 0 = Write  
	I2C_write(READ_CONFIG_CMD);
	I2C_restart();
	I2C_write((SI7021_ADDR << 1) | 1);  // 1 = Read 	
	data = I2C_read(NACK);						

	I2C_stop();

	return data;
}
//------------------------------------------------------------------------------
void SI7021_writeConfig(uint8_t data)
{	
	uint8_t config = SI7021_readConfig();

	I2C_start(); 

	I2C_write((SI7021_ADDR << 1) | 0);  // 0 = Write  
	I2C_write(WRITE_CONFIG_CMD);						
	I2C_write(data | config);

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
	uint8_t data[3] = {0, 0, 0}; 

	SI7021_command(command);
	delay(30);				
		
	I2C_start();

	I2C_write((SI7021_ADDR << 1) | 1);  // 1 = Read 	
	data[0] = I2C_read(ACK);			// MSB
	data[1] = I2C_read(ACK);			// LSB
	data[2] = I2C_read(NACK);			// CRC

	I2C_stop();

	return (SI7021_isDataValid(data)) ? (data[0] << 8) + data[1] : 0xFFFF;
}
//------------------------------------------------------------------------------
float SI7021_calcHumd(uint16_t rawHumd)
{
	return ( ((float)rawHumd * 125) / 65536 ) - 6;
}
//------------------------------------------------------------------------------
float SI7021_calcTemp(uint16_t rawTemp) 
{
	return ( ((float)rawTemp * 175.72f) / 65536) - 46.85f;
}
//------------------------------------------------------------------------------
uint8_t SI7021_calcCRC(uint8_t data[])
{
	uint8_t i, crc = 0, size = 2;

	while(size--)
	{
		crc ^= *data++;

		for(i = 0; i < 8; i++) 
		{
			crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);  //0x131 (see datasheet) x^8 + x^5 + x^4 + 1 => 0b 0001 0011 0001
		}
	}
	
	return crc; 
}
//------------------------------------------------------------------------------
uint8_t SI7021_isDataValid(uint8_t data[])
{
	uint8_t isValid = 0;
	
	if(SI7021_calcCRC(data) == data[2])        // data[2] == CRC value
	{
		isValid = 1;
	}
	
	return isValid;
}
//------------------------------------------------------------------------------
#endif