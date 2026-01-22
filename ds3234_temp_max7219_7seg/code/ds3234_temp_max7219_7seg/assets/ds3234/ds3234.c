#ifndef DS3234_C
#define	DS3234_C
//------------------------------------------------------------------------------
#include "ds3234.h"
uint8_t CS2  = 8;
//------------------------------------------------------------------------------
void ds3234_init()
{
  spi_init();   
  
  pinMode(CS2, OUTPUT);
  digitalWrite(CS2, HIGH);      //CS2 = 1;      //Deselect initially
  
  ds3234_write(control_reg, 0x20);
  ds3234_write(status_reg, 0x48);
}
//------------------------------------------------------------------------------
uint8_t ds3234_read(uint8_t address)
{ 
	uint8_t data = 0;
  digitalWrite(CS2, LOW);       //CS2 = 0;

  spi_write(address + read_cmd);
  data = spi_read(); 
  
  digitalWrite(CS2, HIGH);      //CS2 = 1;

  return data;
}
//------------------------------------------------------------------------------
void ds3234_write(uint8_t address, uint8_t data)
{
  digitalWrite(CS2, LOW);       //CS2 = 0;

  spi_write(address + write_cmd);
  spi_write(data);
  
  digitalWrite(CS2, HIGH);      //CS2 = 1;
}
//------------------------------------------------------------------------------
void ds3234_setTime(uint8_t time[])
{  
	for(uint8_t reg = 0; reg < 7 ;reg++)
  {
    uint8_t data = calc_BCDTime(time[reg]);
    ds3234_write(reg, data);              //Sec,Min,Hour,WDay,MDay,Month,Year
  }
}
//------------------------------------------------------------------------------
void ds3234_getTime(uint8_t time[])
{	
  for(uint8_t reg = 0; reg < 7; reg++)
  {
    uint8_t data = ds3234_read(reg);
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
uint16_t ds3234_getRawTemp(void)
{
	uint16_t data_[2];
	
	data_[0] = ds3234_read(tempLSB_REG);
	data_[1] = ds3234_read(tempMSB_REG);
	
	return (data_[1] << 8) | data_[0];
}
//------------------------------------------------------------------------------
float ds3234_getTemp(void)
{	
	uint16_t rawTemp = ds3234_getRawTemp();
	return toFloat(rawTemp);
}
//------------------------------------------------------------------------------
float toFloat(int16_t rawData)
{
	float tempr  =  rawData >> 8; // Get the integer part    
	int16_t count =  rawData & FRAC_FLAG;          
																			 
	if(count) 
	{
		tempr += ((count >> 6) * 0.25); // Get the integer part. 2^(-2) = 0.25 (result is in multiples of 0.25 LSBit for 10-bit_ res ADC)
	}

	return tempr;
}
//------------------------------------------------------------------------------
#endif