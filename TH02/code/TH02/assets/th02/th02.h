#ifndef TH02_H
#define	TH02_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
//------------------------------------------------------------------------------
#define		STATUS_REG      0x00
#define		CONFIG_REG      0x03
#define		DEV_ID_REG      0x11
#define		FAST_MODE       0x20
#define		TH02_ADDR       0x40      // 7-bit I2C sensor address (check your datasheet)
#define 	TEMP_CMD 		0x11      // Command to initiate a temperature measurement
#define		HUMD_CMD  		0x01      // Command to initiate a humidity measurement
#define 	TEMP_FAST_CMD   0x31      // Command to initiate a temperature measurement
#define		HUMD_FAST_CMD   0x21      // Command to initiate a humidity measurement
//------------------------------------------------------------------------------
void		TH02_init(void);
uint8_t 	TH02_readDevice(uint8_t command);
uint16_t	TH02_readConv(uint8_t command);
void		TH02_command(uint8_t command);
float		TH02_getTemp(void);
float		TH02_getHumd(void);
//------------------------------------------------------------------------------
#endif