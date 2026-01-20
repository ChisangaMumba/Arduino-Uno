#ifndef TC77_C
#define TC77_C
//------------------------------------------------------------------------------
#include "../SPI/Soft_SPI.h"
#include "tc77.h"
//------------------------------------------------------------------------------
uint8_t CS2  = 8;
//------------------------------------------------------------------------------
void TC77_init(void)
{
  SPI_init();

  pinMode(CS2, OUTPUT);
  digitalWrite(CS2, HIGH);   // unselect initially

  delay(300);
}
//------------------------------------------------------------------------------
int16_t TC77_read(void)
{   
  uint8_t data_[2];  
  
  digitalWrite(CS2, LOW);     // CS2 = 0;
  
  data_[1] = SPI_read();      // MSB     
  data_[0] = SPI_read();      // LSB
  
  digitalWrite(CS2, HIGH);    // CS2 = 1;
  
	return (data_[1] << 8) + data_[0];
}
//------------------------------------------------------------------------------
float TC77_getTemp(void)
{
  int16_t temp = TC77_read();

  return toFloat(temp);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
  float result = (tempr >> 7);     
  uint8_t count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
    result += ((count >> 3) * 0.0625);  
  }
  
  return result;
}
//------------------------------------------------------------------------------
#endif 