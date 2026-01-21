#ifndef mcp9800_H
#define	mcp9800_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
//----------------------------MCP9800-------------------------------------------
#define  ADDR        0x90        // Device Address
#define  TEMP_REG    0x00
#define  CONFIG_REG  0x01
#define  THYST_REG   0x02
#define  TSET_REG    0x03
#define  RES09_BIT	 0x00		 // 0.5°C (Power-up default)
#define  RES10_BIT	 0x20		 // 0.25°C 
#define  RES11_BIT	 0x40		 // 0.125°C
#define  RES12_BIT	 0x60		 // 0.0625°C
#define  Rd          1
#define  Wr          0
#define  FRAC_FLAG	 0x00F0      // Fractional part of temperature
//------------------------------------------------------------------------------
void     mcp9800_init(uint8_t res);
void     mcp9800_write(uint8_t reg, uint16_t settings);
int16_t  mcp9800_read(uint8_t reg);
void     mcp9800_setConfig(uint8_t settings);
uint8_t  mcp9800_getConfig(void);
uint8_t  mcp9800_getResNum(void);
float    mcp9800_getTemp(void);
float    toFloat(int16_t tempr);
//------------------------------------------------------------------------------
#endif