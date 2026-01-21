#ifndef MAX7219_H
#define	MAX7219_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#include "ascii_chars.h"
uint8_t CS  = 10;  
//------------------------------------------------------------------------------
#define NO_OP_REG           0x00     //Used for max7219 Cascading purposes
#define DECODE_MODE_REG     0x09
#define INTESITY_REG        0x0A
#define SCAN_LIMIT_REG      0x0B
#define SHUTDOWN_REG        0x0C
#define DISPLAY_TEST_REG    0x0F
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define BRIGHTNESS          0x0F     //Can be alterterd to suite requirement
#define SCAN_ALL_DIGITS     0x07   
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST        0x00   
//------------------------------------------------------------------------------
void max7219_init(uint8_t noChips);
void max7219_config(uint8_t chip);
void max7219_write(uint8_t regName, uint8_t data, uint8_t chip);
void max7219_displayText(uint8_t * text);
void max7219_NoOperation(void);
void writeChar(uint8_t chr, uint8_t chip);
void displayDp(uint8_t chr, uint8_t chip);
//------------------------------------------------------------------------------
#endif