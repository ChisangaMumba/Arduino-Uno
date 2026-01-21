#ifndef TC72_H
#define TC72_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
uint8_t CS2  = 9; 
//------------------------------------------------------------------------------
#define CONTROL_REG     0x80
#define START_CONV      0x00
#define LSB_REG         0x01
#define MSB_REG     	0x02
#define MANF_ID_REG     0x03
#define FRAC_FLAG       0x00C0
//------------------------------------------------------------------------------
void    tc72_init(void);
int16_t tc72_read(uint8_t regName);
float   tc72_getTemp(void);
float   tc72_getTemp2(void);
float   toFloat(int16_t tempr); 
//------------------------------------------------------------------------------
#endif // TC77_H   