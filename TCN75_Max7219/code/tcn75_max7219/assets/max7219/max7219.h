#ifndef MAX7219_H
#define	MAX7219_H
//------------------------------------------------------------------------------
#include "../SPI/Soft_SPI.h"
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
void max7219_displayNumber(signed long number);
void max7219_displayText(uint8_t text[]);
void writeChar(uint8_t chr, uint8_t chrPos, int8_t  dpPos);
uint8_t getDigit(uint8_t chr, uint8_t chrPos, int8_t dpPos);
void setDpPos(int8_t dpPos[], uint8_t chars[]);
uint8_t getCustomChar(uint8_t chr);
//------------------------------------------------------------------------------
//Common Cathode          0,    1,    2,    3,    4,    5,    6,    7,    8,   9
uint8_t digits[10] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x73 };
//----------------------------Custom characters---------------------------------
uint8_t chars[]    = {  '-',  ' ',  'C',  'F',  '°',  '%',  'E',  'O',  'R',  'T', '\0' };
uint8_t charCode[] = { 0x01, 0x00, 0x4E, 0x47, 0x63, 0x67, 0x4F, 0x1D, 0x05, 0x0F, '\0' };
//------------------------------------------------------------------------------
#endif