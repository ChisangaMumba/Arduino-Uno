#ifndef TM1638_H
#define TM1638_H
//-----------------------------------------------------------------------------------
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
//-----------------------------------------------------------------------------------
#include "charset.h"
#include "../serial/serial.h"
//-----------------------------------------------------------------------------------
#define DISPLAY_REG0  0xC0
#define DECIMAL_POINT 0x80
//-----------------------------------------------------------------------------------
void serialOut(uint8_t dir, uint8_t data);
uint8_t serialIn(uint8_t dir);
//-----------------------------------------------------------------------------------
void tm1638_init(uint8_t brightness);
void tm1638_command(uint8_t command);
void tm1638_data(uint8_t reg, uint8_t data);
void tm1638_setBrightness(uint8_t brightness);
void tm1638_clearDisplay(void);
void tm1638_print(const char* format, ...);
void tm1638_string(uint8_t str[]);
void tm1638_writeLed(uint8_t ledPos, uint8_t data);
void tm1638_pulseLed(uint8_t pos);
uint8_t tm1638_readButtons(void);
void ledFeedback(uint8_t buttons);
void writeChar(uint8_t reg, uint8_t chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos);
uint8_t getCustomChar(uint8_t chr);
void setDpPos(int8_t dpPos[], uint8_t chars[]);
//-----------------------------------------------------------------------------------
#endif