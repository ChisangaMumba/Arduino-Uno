#ifndef TC74_H
#define	TC74_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
//------------------------------------------------------------------------------
#define  TEMPR_REG     	     0x00
#define  CONFIG_REG          0x01
#define  READ                0x9A     
#define  WRITE               0x9B     
#define  STANDBY_MODE	     0x80
#define  NORMAL_MODE		 0x00
#define	 DEG_SYMBOL			 0xDF     //223 (0xDF) is � symbol. Not a standard ascii character
//------------------------------------------------------------------------------
void TC74_init(uint8_t data);
void TC74_config(uint8_t data);
int8_t TC74_read(uint8_t regAddress);
//------------------------------------------------------------------------------
#endif