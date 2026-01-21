#ifndef TC77_H
#define TC77_H
//------------------------------------------------------------------------------
#include "../soft_spi/soft_spi.c"
//------------------------------------------------------------------------------
#define SHUTDOWN     	   0xFF
#define CONTINUOUS_CONV    0x00
#define FRAC_FLAG          0x0078
//------------------------------------------------------------------------------
void    tc77_init(uint8_t CS_pin);
int16_t tc77_read(void);
float   tc77_getTemp(void);
float   toFloat(int16_t tempr); 
//------------------------------------------------------------------------------
#endif // TC77_H   