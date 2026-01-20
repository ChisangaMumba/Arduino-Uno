#ifndef mcp9800_H
#define	mcp9800_H
//------------------------------------------------------------------------------
#include "../I2C/I2C.h"
//----------------------------mcp9800--------------------------------------------
#define TEMP_REG    0x00
#define CONFIG_REG  0x01
#define THYST_REG  	0x02
#define TSET_REG   	0x03
#define RES09_BIT	0x00		 //0.5°C (Power-up default)
#define RES10_BIT	0x20		 //0.25°C 
#define RES11_BIT	0x40		 //0.125°C
#define RES12_BIT	0x60		 //0.0625°C
#define Rd          1
#define Wr          0
#define	DEG_SYMBOL	0xDF     //223 (0xDF) is ° symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void mcp9800_init(uint8_t addr, uint8_t res);
void mcp9800_write(uint8_t addr, uint8_t reg, uint16_t settings);
int16_t  mcp9800_read(uint8_t addr, uint8_t reg);
void mcp9800_writeConfig(uint8_t addr, uint8_t settings);
uint8_t mcp9800_getResolutionNum(uint8_t addr);
uint8_t mcp9800_readConfig(uint8_t addr);
float mcp9800_getTemperature(uint8_t addr);
float calcTemp(int16_t tempr, uint8_t resInd);
//------------------------------------------------------------------------------
float resValues[4] = { 0.5, 0.25, 0.125, 0.0625 }; // 2^(-1), 2^(-2), 2^(-3), 2^(-4)
//------------------------------------------------------------------------------
#endif