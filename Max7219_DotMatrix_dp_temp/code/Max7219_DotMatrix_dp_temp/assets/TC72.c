#ifndef TC72_C
#define	TC72_C
//------------------------------------------------------------------------------
#include "TC72.h"
uint8_t CS2  = 9;
//------------------------------------------------------------------------------
void TC72_init()
{
  pinMode(CS2, OUTPUT);
  digitalWrite(CS2, LOW);       //CS2 = 0		//Deselect initially
	
  digitalWrite(CS2, HIGH);      //CS2 = 1
  
  SPI_write(CONTROL_REG);
  SPI_write(START_CONV);				//Continous conversion
  
  digitalWrite(CS2, LOW);       //CS2 = 0
  delay(150);
}
//------------------------------------------------------------------------------
int TC72_readTempr()
{ 
  unsigned char tempr[2]; 
    
  digitalWrite(CS2, HIGH);      //CS2 = 1
  
  SPI_write(TEMPR_REG);                  //Access Tempr register for reading
  tempr[1] = SPI_read();     
  tempr[0] = SPI_read();
  
  digitalWrite(CS2, LOW);       //CS2 = 0
  
  return ((tempr[1] << 8) + tempr[0]);
}
//------------------------------------------------------------------------------
float calcTempr(signed int tempr)
{
  float result = (float)(tempr >> 8);      //Discard LSByte (Only holds fraction flag bits)
  int count = tempr & FRAC_FLAG;          
  
  if(count) 
  { 
    result += ((count >> 6) * 0.25);
  }
  
  return (result);
}
//------------------------------------------------------------------------------
#endif