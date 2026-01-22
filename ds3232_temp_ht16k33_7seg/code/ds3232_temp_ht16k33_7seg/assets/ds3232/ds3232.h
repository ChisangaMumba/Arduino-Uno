#ifndef DS3232_H
#define	DS3232_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
#include "time_functions.h"
//------------------------------------------------------------------------------
#define WR 0
#define RD 1
//------------------------------------------------------------------------------
#define tempMSB_REG                  0x11
#define tempLSB_REG                  0x12
#define FRAC_FLAG		 	         0x00C0
//------------------------------------------------------------------------------
void ds3232_init(void);
void ds3232_setDateTime(uint8_t time[]);
void ds3232_getDateTime(uint8_t time[]);
uint8_t ds3232_read(uint8_t address);
uint16_t ds3232_getRawTemp(void);
float ds3232_getTemp(void);
float toFloat(int16_t rawData);
//------------------------------------------------------------------------------
#endif