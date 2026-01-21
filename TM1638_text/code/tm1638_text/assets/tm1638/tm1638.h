#ifndef TM1638_H
#define TM1638_H
//-----------------------------------------------------------------------------------
#include "../serial/serial.h"
#define DISPLAY_REG0  0xC0
#define DECIMAL_POINT 0x80
//-----------------------------------------------------------------------------------
void serialOut(uint8_t dir, uint8_t data);
uint8_t serialIn(uint8_t dir);
//-----------------------------------------------------------------------------------
void TM1638_init(uint8_t brightness);
void TM1638_command(uint8_t command);
void TM1638_data(uint8_t reg, uint8_t data);
void TM1638_setBrightness(uint8_t brightness);
void TM1638_clearDisplay();
void TM1638_writeDisplay(uint8_t text[]);
void TM1638_writeLed(uint8_t ledPos, uint8_t data);
void TM1638_pulseLed(uint8_t pos);
uint8_t TM1638_readButtons();
void ledFeedback(uint8_t buttons);
void writeChar(uint8_t reg, uint8_t chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos);
uint8_t getCustomChar(uint8_t chr);
void getDpPos(int8_t dpPos[], uint8_t chars[]);
//-----------------------------------------------------------------------------------
//Common Anode              0,    1,    2,    3,    4,    5,    6,    7,    8,   9
uint8_t digits[10] =   { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//--------------------------------Custom characters----------------------------------
uint8_t customChar[] = {  '-',  ' ',  '°',  'C',  'F',  '%',  'T',  'D',  'E',  'O',  'R',  'P',  'H',  'L',  'A',  'N', '\0' };
uint8_t charCode[]   = { 0x40, 0x00, 0x63, 0x39, 0x71, 0x73, 0x78, 0x5E, 0x79, 0x3F, 0x50, 0x73, 0x74, 0x38, 0x77, 0x54, '\0' };
//-----------------------------------------------------------------------------------
#endif