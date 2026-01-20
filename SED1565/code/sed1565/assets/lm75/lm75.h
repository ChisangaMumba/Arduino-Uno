#ifndef LM75_H
#define	LM75_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
//------------------------------------------------------------------------------
#define  LM75_ADDRESS           0x90     // Address + Read bit
#define  TEMP_REG      			0x00
#define  CONFIG_REG    			0x01
#define  THYST_REG            	0x02     
#define  TOS_REG              	0x03
#define  FRACTION_FLAG          0x0080   // 0.5 Bit Flag
#define	 DEG_SYMBOL				0xDF     //223 (0xDF) is ° symbol. Not a standard ascii uint8_tacter
//------------------------------------------------------------------------------
void    lm75_init(int16_t tempH, int16_t tempL);
int16_t lm75_read(uint8_t regAddress);
void    lm75_setConfig(uint8_t _data);
uint8_t lm75_readConfig(void);
void    lm75_set(uint8_t regAddress, int16_t _data);
float   lm75_getTemp();
float   toFloat(int16_t tempr);
//------------------------------------------------------------------------------
#endif