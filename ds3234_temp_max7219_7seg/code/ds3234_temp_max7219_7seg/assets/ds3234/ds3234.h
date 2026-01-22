#ifndef DS3234_H
#define	DS3234_H
//------------------------------------------------------------------------------
#include "../SPI/soft_SPI.h"
//------------------------------------------------------------------------------
#define read_cmd                     0x00
#define write_cmd                    0x80
//------------------------------------------------------------------------------
#define control_reg                  0x0E
#define status_reg                   0x0F
//------------------------------------------------------------------------------
#define tempMSB_REG                  0x11
#define tempLSB_REG                  0x12
#define FRAC_FLAG		 	         0x00C0
//------------------------------------------------------------------------------
void ds3234_init();
uint8_t ds3234_read(uint8_t addr);
void ds3234_write(uint8_t addr, uint8_t data);
void ds3234_setTime(uint8_t time[]);
void ds3234_getTime(uint8_t time[]);
uint8_t calc_DecTime(uint8_t time);
uint8_t calc_BCDTime(uint8_t time);
uint16_t ds3234_getRawTemp(void);
float ds3234_getTemp(void);
float toFloat(int16_t rawData);
//------------------------------------------------------------------------------
#endif