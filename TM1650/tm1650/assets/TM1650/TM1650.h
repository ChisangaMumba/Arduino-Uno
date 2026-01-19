#ifndef TM1650_H
#define TM1650_H
//------------------------------------------------------------------------------
// #include <Wire.h>               // For hardware I2C
#include "../I2C/I2C.c"
//------------------------------------------------------------------------------
#define TM1650_ADDRESS_BASE   0x34 // Address of the left-most digit
#define TM1650_DCTRL_BASE     0x24 // Address of the control register of the left-most digit
#define DECIMAL_POINT         0x80
//------------------------------------------------------------------------------
void tm1650_init();
void tm1650_data(uint8_t address, uint8_t data);
void tm1650_clear();
void tm1650_displayOn(uint8_t brightness);
void tm1650_displayNum(int16_t number);
void tm1650_displayStrNum(char text[]); 
void writeChar(uint8_t count, uint8_t chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos);
uint8_t getCustomChar(uint8_t chr);
void getDpPos(int8_t dpPos[], uint8_t chars[]);
//------------------------------------------------------------------------------
//Common Anode          0,    1,    2,    3,    4,    5,    6,    7,    8,   9
uint8_t digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//----------------------------Custom characters---------------------------------
uint8_t customChar[] = {  '-',  ' ',  '°',  'C',  'F',  '%',  'T',  'D',  'E', 'O',  'R',  'P',  'H',  'L', '\0' };
uint8_t charCode[]   = { 0x40, 0x00, 0x63, 0x39, 0x71, 0x73, 0x78, 0x5E, 0x79,0x3F, 0x50, 0x73, 0x76, 0x38, '\0' };
//------------------------------------------------------------------------------
#endif