#ifndef DS3234_C
#define	DS3234_C
//------------------------------------------------------------------------------
#include "ds3234.h"
uint8_t CS2  = 8;
//------------------------------------------------------------------------------
void DS3234_init()
{
  SPI_init();   
  
  pinMode(CS2, OUTPUT);
  digitalWrite(CS2, HIGH);      //CS2 = 1;      //Deselect initially
  
  DS3234_write(control_reg, 0x20);
  DS3234_write(status_reg, 0x48);
}
//------------------------------------------------------------------------------
uint8_t DS3234_read(uint8_t address)
{ 
	uint8_t data = 0;
  digitalWrite(CS2, LOW);       //CS2 = 0;

  SPI_write(address + read_cmd);
  data = SPI_read(); 
  
  digitalWrite(CS2, HIGH);      //CS2 = 1;

  return data;
}
//------------------------------------------------------------------------------
void DS3234_write(uint8_t address, uint8_t data)
{
  digitalWrite(CS2, LOW);       //CS2 = 0;

  SPI_write(address + write_cmd);
  SPI_write(data);
  
  digitalWrite(CS2, HIGH);      //CS2 = 1;
}
//------------------------------------------------------------------------------
void DS3234_setTime(uint8_t time[])
{  
	for(uint8_t reg = 0; reg < 7 ;reg++)
  {
    uint8_t data = calc_BCDTime(time[reg]);
    DS3234_write(reg, data);              //Sec,Min,Hour,WDay,MDay,Month,Year
  }
}
//------------------------------------------------------------------------------
void DS3234_getTime(uint8_t time[])
{	
  for(uint8_t reg = 0; reg < 7; reg++)
  {
    uint8_t data = DS3234_read(reg);
    time[reg] = calc_DecTime(data);        //Sec,Min,Hour,WDay,MDay,Month,Year
  }
}
//-----------------------Change BCD time to Decimal-----------------------------
uint8_t calc_DecTime(uint8_t time)
{   
  return ((time >> 4) * 10) + (time & 0x0F);  
}
//-----------------------Change Decimal time to BCD-----------------------------
uint8_t calc_BCDTime(uint8_t time)
{
  return ((time / 10) << 4) + (time % 10);
}
//------------------------------------------------------------------------------
#endif