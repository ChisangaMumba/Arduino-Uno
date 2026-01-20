#ifndef SAA1064_H
#define	SAA1064_H
//------------------------------------------------------------------------------
#include "../I2C/I2C.h"
//------------------------------------------------------------------------------
#define SAA1064_ADDRESS  0x70      //Address bits can be altered on device if wished
#define CONTROL_REG      0x00      
#define DISPLAY_REG      0x01      
#define DEVICE_CONFIG    0x47      //adds 12 mA to segment output current. dynamic mode 
#define DECIMAL_POINT    0x80
//------------------------------------------------------------------------------
void SAA1064_init(void);
void SAA1064_displayInt(int16_t num);
void SAA1064_displayText(uint8_t text[]);
void SAA1064_write(uint8_t text[]);
void writeChar(uint8_t chrPos, int8_t dpPos, uint8_t chr);
uint8_t getCustomChar(uint8_t chr);
uint8_t getDigit(uint8_t charPos, int8_t dpPos, uint8_t chr);
int8_t findPosChar(uint8_t chars[], uint8_t toFind);
uint8_t* getLastCharAddr(uint8_t text[]);
//------------------------------------------------------------------------------
//Common Cathode          0,    1,    2,    3,    4,    5,    6,    7,    8,   9
uint8_t digits[]   = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//----------------------------Custom characters---------------------------------
uint8_t chars[]    = {  '-',  ' ',  '°',  'C',  'F',  '%',  'E', 'O',  'R', '\0' };
uint8_t charCode[] = { 0x40, 0x00, 0x63, 0x4E, 0x47, 0x67, 0x4F,0x1D, 0x05, '\0' };
//------------------------------------------------------------------------------
#endif	/* SAA1064_PROTOTYPES_H */