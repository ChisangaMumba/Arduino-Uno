#ifndef HT16K33_H
#define	HT16K33_H
//------------------------------------------------------------------------------
#include "../I2C/I2C.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define HT16K33_ADDRESS  0xE0      //Address bits can be altered on device if wished
#define OSCILLATOR_ON    0x21      //HT16K33 internal oscillator
#define DIGITAL_DIM      0xE0      
#define DISPLAY_SETUP    0x81
#define DISPLAY_MEMORY   0x00      //Start address. auto increments on every write. valid from 0x00 - 0xFF then auto wraps after last valid address
#define DECIMAL_POINT    0x4000
//------------------------------------------------------------------------------
void ht16k33_init(uint8_t brightness);
void ht16k33_on(void);
void ht16k33_blink(uint8_t _data);
void ht16k33_setBrightness(uint8_t _data);
void ht16k33_displayNum(signed long int number);
void ht16k33_displayText(uint8_t text[]);
void ht16k33_write(uint8_t text[]);
void writeChar(uint8_t chr);
uint16_t getDigit(uint8_t chr);
//------------------------------------------------------------------------------
#endif	/* HT16K33_PROTOTYPES_H */