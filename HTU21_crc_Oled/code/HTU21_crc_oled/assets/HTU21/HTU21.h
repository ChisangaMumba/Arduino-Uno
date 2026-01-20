#ifndef HTU21_H
#define	HTU21_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
//------------------------------------------------------------------------------
#define		WRITE_CONFIG_CMD	0xE6
#define		READ_CONFIG_CMD		0xE7
#define		RESET_CMD    		0xFE	// Software reset
#define		HTU21_ADDR     		0x40	// 7-bit I2C sensor address (check your datasheet)
#define 	TEMP_NO_HOLD_CMD	0xF3	// Command to initiate a temperature measurement
#define		HUMD_NO_HOLD_CMD	0xF5	// Command to initiate a humidity measurement
//------------------------------------------------------------------------------
												// RH				Temp
#define		RES_0    			0x00			// 12bit		14bit
#define		RES_1    			0x01			//  8bit		12bit
#define		RES_2    			0x80			// 10bit		13bit
#define		RES_3    			0x81			// 11bit		11bit
//------------------------------------------------------------------------------
void		HTU21_init(uint8_t res);
uint8_t		HTU21_readConfig(void);
void		HTU21_writeConfig(uint8_t data_);
uint16_t	HTU21_readConv(uint8_t command);
void		HTU21_command(uint8_t command);
float		HTU21_getTemp(uint16_t rawHumd);
float		HTU21_getHumd(uint16_t rawTemp);
uint8_t 	HTU21_calcCRC(uint8_t data[], uint8_t size);
uint8_t 	HTU21_isDataValid(uint8_t data[], uint8_t size);
//------------------------------------------------------------------------------
#endif