#ifndef SI7021_PROTOTYPES_H
#define	SI7021_PROTOTYPES_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
//------------------------------------------------------------------------------
#define		WRITE_CONFIG_CMD	0xE6
#define		READ_CONFIG_CMD		0xE7
#define		RESET_CMD    		0xFE	// Software reset
#define		SI7021_ADDR     	0x40	// 7-bit I2C sensor address (check your datasheet)
#define 	TEMP_NO_HOLD_CMD	0xF3	// Command to initiate a temperature measurement
#define		HUMD_NO_HOLD_CMD	0xF5	// Command to initiate a humidity measurement
//------------------------------------------------------------------------------
										// RH				Temp
#define		RES_0    			0x00	// 12bit		14bit
#define		RES_1    			0x01	//  8bit		12bit
#define		RES_2    			0x80	// 10bit		13bit
#define		RES_3    			0x81	// 11bit		11bit
//------------------------------------------------------------------------------
void		SI7021_init(uint8_t res);
uint8_t		SI7021_readConfig(void);
void		SI7021_writeConfig(uint8_t data_);
uint16_t	SI7021_readConv(uint8_t command);
void		SI7021_command(uint8_t command);
float		SI7021_calcHumd(uint16_t rawHumd);
float		SI7021_calcTemp(uint16_t rawTemp);
uint8_t 	SI7021_calcCRC(uint8_t data[]);
uint8_t		SI7021_isDataValid(uint8_t data[]);
//------------------------------------------------------------------------------
#endif