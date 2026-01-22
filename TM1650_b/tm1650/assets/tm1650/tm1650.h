#ifndef TM1650_H
#define TM1650_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
//------------------------------------------------------------------------------
#include "charset.h"
#include "../i2c/i2c.c"
//------------------------------------------------------------------------------
#define TM1650_ADDRESS_BASE   0x34 // Address of the left-most digit
#define TM1650_DCTRL_BASE     0x24 // Address of the control register of the left-most digit
#define DECIMAL_POINT         0x80
//------------------------------------------------------------------------------
void tm1650_init(uint8_t level);
void tm1650_data(uint8_t address, uint8_t data);
void tm1650_clear(void);
void tm1650_displayOn(uint8_t brightness);
void tm1650_print(const char* format, ...);
void tm1650_string(char text[]); 
void writeChar(uint8_t chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos);
void setDpPos(int8_t dpPos[], char chars[]);
//------------------------------------------------------------------------------
#endif