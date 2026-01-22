#ifndef MAX7219_H
#define	MAX7219_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#include "charset.h"
//------------------------------------------------------------------------------
uint8_t CS = 10;
//------------------------------------------------------------------------------
#define DECODE_MODE_REG     0x09
#define INTESITY_REG        0x0A
#define SCAN_LIMIT_REG      0x0B
#define SHUTDOWN_REG        0x0C
#define DISPLAY_TEST_REG    0x0F
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define DECODE_ALL          0xFF
#define BRIGHTNESS          0x0F
#define SCAN_LOW_NIBBLE     0x03
#define SCAN_ALL_DIGITS     0x07   
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST_MODE   0x00
#define ENABLE_TEST_MODE    0x01
#define DECIMAL_POINT       0x80
//------------------------------------------------------------------------------
void max7219_init(uint8_t scanSize);
void max7219_write(uint8_t reg, uint8_t data);
void max7219_displayNumber(int32_t number);
void max7219_displayText(uint8_t text[]);
void writeChar(uint8_t chr, uint8_t chrPos, int8_t  dpPos);
uint8_t getDigit(uint8_t chr, uint8_t chrPos, int8_t dpPos);
void setDpPos(int8_t dpPos[], uint8_t chars[]);
//------------------------------------------------------------------------------
#endif