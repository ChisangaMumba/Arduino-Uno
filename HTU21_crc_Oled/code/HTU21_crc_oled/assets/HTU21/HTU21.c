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
	uint8_t data[3] = { 0, 0, 0 }; 

	HTU21_command(command);
	delay(50);				
		
	I2C_start();

	I2C_write((HTU21_ADDR << 1) | 1);	// 1 = Read 	
	data[0] = I2C_read(ACK);			// MSB
	data[1] = I2C_read(ACK);			// LSB
	data[2] = I2C_read(NACK);			// CRC

	I2C_stop();

	return (HTU21_isDataValid(data, 2)) ? (data[0] << 8) + data[1] : 0xFFFF;
}
//------------------------------------------------------------------------------
float HTU21_getHumd(uint16_t rawHumd)
{
	return ( ((float)rawHumd *125) / 65536 ) - 6;
}
//------------------------------------------------------------------------------
float HTU21_getTemp(uint16_t rawTemp)
{
	return ( ((float)rawTemp * 175.72f) / 65536) - 46.85f;
}
//------------------------------------------------------------------------------
uint8_t HTU21_calcCRC(uint8_t data[], uint8_t size)
{
	uint8_t i, crc = 0;

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
uint8_t HTU21_isDataValid(uint8_t data[], uint8_t size)
{
	return (HTU21_calcCRC(data, size) == data[2]) ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif