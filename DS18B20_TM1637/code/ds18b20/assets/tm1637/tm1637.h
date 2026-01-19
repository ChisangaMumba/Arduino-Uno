#ifndef TM1637_H
#define TM1637_H
//------------------------------------------------------------------------------
#include "twoWire.h"
//------------------------------------------------------------------------------
#define DISPLAY_MODE  0x40  //Or Keyscan mode 0x42
#define DISPLAY_CTRL  0x87
#define DISPLAY_REG0  0xC0
#define DECIMAL_POINT 0x80
//------------------------------------------------------------------------------
void TM1637_init(uint8_t level);
void TM1637_displayNum(signed int number);
void TM1637_displayNumText(uint8_t text[]);
void TM1637_setBrightness(uint8_t brightness);
void TM1637_write(uint8_t text[]);
void TM1637_command(uint8_t command);
void TM1637_initSend(uint8_t command);
void writeChar(uint8_t chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos);
uint8_t getCustomChar(uint8_t chr);
void getDpPos(int8_t dpPos[], uint8_t chars[]);
//------------------------------------------------------------------------------
//Common Anode          0,    1,    2,    3,    4,    5,    6,    7,    8,   9
const uint8_t digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//----------------------------Custom characters---------------------------------
const uint8_t customChar[] = {  '-',  ' ',  '°',  'C',  'F',  '%',  'T',  'D',  'E', 'O',  'R',  'P',  'H',  'L', '\0' };
const uint8_t charCode[]   = { 0x40, 0x00, 0x63, 0x39, 0x71, 0x73, 0x78, 0x5E, 0x79,0x5C, 0x50, 0x73, 0x76, 0x38, '\0' };
//------------------------------------------------------------------------------
#endif