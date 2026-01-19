
#ifndef SR_74HC595_H
#define	SR_74HC595_H
//------------------------------------------------------------------------------
#include "../SPI/Soft_SPI.h"
//------------------------------------------------------------------------------
#define  FIFO           0   //FIFO - First In First Out
#define  LIFO           1   //LIFO - Last In First Out
#define  DECIMAL_POINT  0x7F
//------------------------------------------------------------------------------
void ShiftReg_LIFOSend(uint8_t text[]);
void ShiftReg_FIFOSend(uint8_t text[]);
uint8_t getDigit(uint8_t chr, uint8_t charPos, int8_t dpPos);
uint8_t getCustomChar(uint8_t chr);
int8_t findPosChar(uint8_t chars[], uint8_t toFind);
void writeChar(uint8_t chr, uint8_t charPos, int8_t dpPos);
uint8_t* get_lastCharAddr(uint8_t text[]);
//-------------------------Common Anode-----------------------------------------
                      //   0 , 1  ,  2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  8 ,  9
uint8_t digits[10] = { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90 }; 
//----------------------------Custom characters---------------------------------
uint8_t customChar[] = {  '-',  ' ',  '�',  'C',  'F',  '%',  'E', 'O',  'R', 'P', '\0'};
uint8_t charCode[]   = { 0xBF, 0xFF, 0x9c, 0xC6, 0x8E, 0x8C, 0x86,0xC0, 0xCE,0x98, '\0'};
//------------------------------------------------------------------------------
#endif

