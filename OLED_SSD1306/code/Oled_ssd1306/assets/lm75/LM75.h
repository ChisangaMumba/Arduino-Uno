#ifndef LM75_H
#define	LM75_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
//------------------------------------------------------------------------------
#define  LM75_ADDRESS             0x90     // Address + Read bit
#define  TEMPERATURE_ADDRESS      0x00
#define  CONFIGURATION_ADDRESS    0x01
#define  THYST_ADDRESS            0x02     
#define  TOS_ADDRESS              0x03
#define  FRACTION_FLAG            0x0080   // 0.5 Bit Flag
#define	 DEG_SYMBOL				  0xDF     //223 (0xDF) is � symbol. Not a standard ascii uint8_tacter
//------------------------------------------------------------------------------
void  LM75_init(void);
float LM75_read(uint8_t regAddress);
void  LM75_setConfig(uint8_t _data);
uint8_t  LM75_readConfig(void);
void  LM75_set(uint8_t regAddress, int16_t _data);
float toFloat(int16_t tempr);
//------------------------------------------------------------------------------
#endif