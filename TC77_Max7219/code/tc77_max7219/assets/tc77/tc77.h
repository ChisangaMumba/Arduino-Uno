#ifndef TC77_H
#define TC77_H
//------------------------------------------------------------------------------
#define SHUTDOWN     	   0xFF
#define CONTINUOUS_CONV    0x00
#define FRAC_FLAG          0x0078
//------------------------------------------------------------------------------
void    TC77_init(void);
int16_t TC77_read(void);
float   TC77_getTemp(void);
float   toFloat(int16_t tempr); 
//------------------------------------------------------------------------------
#endif 