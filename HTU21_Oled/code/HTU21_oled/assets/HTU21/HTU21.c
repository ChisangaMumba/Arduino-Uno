#ifndef HTU21_C
#define	HTU21_C
//------------------------------------------------------------------------------
#include "HTU21.h"
//------------------------------------------------------------------------------
void HTU21_init(uint8_t res)
{	
	I2C_init(); 
	
	HTU21_command(RESET_CMD);
	delay(30);
	HTU21_writeConfig(res);
}
//------------------------------------------------------------------------------
uint8_t HTU21_readConfig(void)
{
	uint8_t data = 0;

	I2C_start(); 

	I2C_write((HTU21_ADDR << 1) | 0);  // 0 = Write  
	I2C_write(READ_CONFIG_CMD);
	I2C_restart();
	I2C_write((HTU21_ADDR << 1) | 1);  // 1 = Read 	
	data = I2C_read(NACK);						

	I2C_stop();

	return data;
}
//------------------------------------------------------------------------------
void HTU21_writeConfig(uint8_t data)
{	
	uint8_t config = HTU21_readConfig();

	I2C_start(); 

	I2C_write((HTU21_ADDR << 1) | 0);  // 0 = Write  
	I2C_write(WRITE_CONFIG_CMD);						
	I2C_write(data | config);

	I2C_stop();
}
//------------------------------------------------------------------------------
void HTU21_command(uint8_t command)
{
	I2C_start();                      

	I2C_write((HTU21_ADDR << 1) | 0);  // 0 = Write             
	I2C_write(command);

	I2C_stop(); 
}
//------------------------------------------------------------------------------
uint16_t HTU21_readConv(uint8_t command)
{
	uint8_t data[2] = { 0, 0 }; 

	HTU21_command(command);
	delay(50);				
		
	I2C_start();

	I2C_write((HTU21_ADDR << 1) | 1);  // 1 = Read 	
	data[1] = I2C_read(ACK);			// MSB
	data[0] = I2C_read(NACK);			// LSB

	I2C_stop();

	return (data[1] << 8) + data[0];
}
//------------------------------------------------------------------------------
float HTU21_getHumd()
{
	uint16_t rawHumd = HTU21_readConv(HUMD_NO_HOLD_CMD);

	return ( ((float)rawHumd *125) / 65536 ) - 6;
}
//------------------------------------------------------------------------------
float HTU21_getTemp()
{
	uint16_t rawTemp = HTU21_readConv(TEMP_NO_HOLD_CMD);

	return ( ((float)rawTemp * 175.72f) / 65536) - 46.85f;
}
//------------------------------------------------------------------------------
#endif