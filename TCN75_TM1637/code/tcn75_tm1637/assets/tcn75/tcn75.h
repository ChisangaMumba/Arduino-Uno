#ifndef TCN75_H
#define	TCN75_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
//------------------------------------------------------------------------------
#define  	TCN75_ADDRESS               0x90     // Address + Read bit
#define  	TEMP_REG      				0x00
#define  	CONFIG_REG    				0x01
#define  	THYST_REG            		0x02     
#define  	TOS_REG              		0x03
#define  	FRAC_FLAG            		0x00F0   
//------------------------------------------------------------------------------
#define		RES_09_BIT          		0x00
#define		RES_10_BIT          		0x20
#define		RES_11_BIT          		0x40
#define		RES_12_BIT          		0x60
//------------------------------------------------------------------------------
void    	tcn75_init(int16_t tempH, int16_t tempL, uint8_t res);
int16_t 	tcn75_read(uint8_t regAddress);
void    	tcn75_setConfig(uint8_t _data);
uint8_t 	tcn75_readConfig(void);
void    	tcn75_set(uint8_t regAddress, int16_t _data);
uint8_t     tcn75_getRes(void);
float   	tcn75_getTemp(uint8_t regAddress);
float   	toFloat(int16_t tempr, uint8_t resInd);
//------------------------------------------------------------------------------
uint8_t     RES_INDEX;
float		resValues[4] = { 0.5, 0.25, 0.125, 0.0625 }; // 2^(-1), 2^(-2), 2^(-3), 2^(-4)
//------------------------------------------------------------------------------
#endif