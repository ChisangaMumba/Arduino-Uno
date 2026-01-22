#ifndef TM1637_H
#define TM1637_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
//------------------------------------------------------------------------------
#include "charset.h"
#include "../twoWire/twoWire.c"
//------------------------------------------------------------------------------
#define DISPLAY_MODE  0x40  //Or Keyscan mode 0x42
#define DISPLAY_CTRL  0x87
#define DISPLAY_REG0  0xC0
#define DECIMAL_POINT 0x80
//------------------------------------------------------------------------------
void tm1637_init(uint8_t level);
void tm1637_setBrightness(uint8_t brightness);
void tm1637_print(const char* format, ...);
void tm1637_string(uint8_t text[]);
void tm1637_command(uint8_t command);
void tm1637_initSend(uint8_t command);
void writeChar(uint8_t chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos);
void setDpPos(int8_t dpPos[], uint8_t chars[]);
//------------------------------------------------------------------------------
#endif