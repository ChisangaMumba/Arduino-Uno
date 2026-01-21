#ifndef TC72_C
#define TC72_C
//------------------------------------------------------------------------------
#include "tc72.h"
//------------------------------------------------------------------------------
void tc72_init(void)
{
  spi_init();  
  pinMode(CS2, OUTPUT);

  digitalWrite(CS2, LOW);     // CS2 = 0. Deselect initially
  
  digitalWrite(CS2, HIGH);    // CS2 = 1 

  spi_write(CONTROL_REG);
  spi_write(START_CONV);   // Start continuous conversion

  digitalWrite(CS2, LOW);     // CS2 = 0

  delay(150);                 // Wait for the tc72 to set up
}
//------------------------------------------------------------------------------
int16_t tc72_read(uint8_t regName)
{   
  uint8_t data;  
  
  digitalWrite(CS2, HIGH);      // CS2 = 1
   
  spi_write(regName);   
  data = spi_read();
  
  digitalWrite(CS2, LOW);       // CS2 = 0
  
	return data;
}
//------------------------------------------------------------------------------
float tc72_getTemp(void)
{
  uint8_t data[3];  
  
  digitalWrite(CS2, HIGH);      // CS2 = 1
  
  spi_write(MSB_REG);
  data[2] = spi_read();     // MSB
  data[1] = spi_read();     // LSB, send dummy byte
  // data[0] = spi_read();  // CONTROL Byte, send dummy byte
  
  digitalWrite(CS2, LOW);       // CS2 = 0

  return toFloat((data[2] << 8) + data[1]); // Convert to float temperature
}
//------------------------------------------------------------------------------
float tc72_getTemp2(void)
{ 
  uint8_t data[2];	
	
  data[1] = tc72_read(MSB_REG);				// MSB					  	                  
  data[0] = tc72_read(LSB_REG);				// LSB
	
  
	return toFloat((data[1] << 8) + data[0]);
}
//------------------------------------------------------------------------------
float toFloat(int16_t rawData)
{
  float tempF    = rawData >> 8;  // get the integer part
  uint16_t count = rawData & FRAC_FLAG;          
  
  if(count) 
  {
    tempF += ((count >> 6) * 0.25);  // 0.25f is equivalent to 2^(-2) (result is in multiples of 0.25 LSBit for 10-bit res ADC)
  }
  
  return tempF;
}
//------------------------------------------------------------------------------
#endif 