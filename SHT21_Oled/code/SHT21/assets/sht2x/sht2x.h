#ifndef SHT2x_H
#define SHT2x_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
//------------------------------------------------------------------------------
#define SHT21_I2C_ADDRESS 0x80
#define TEMP_MEASURE      0xF3
#define HUMD_MEASURE      0xF5
//------------------------------------------------------------------------------
void SHT2x_init(void);
uint16_t SHT2x_read(uint8_t command);
float SHT2x_getTemp();
float SHT2x_getHumd(); 
//------------------------------------------------------------------------------
#endif