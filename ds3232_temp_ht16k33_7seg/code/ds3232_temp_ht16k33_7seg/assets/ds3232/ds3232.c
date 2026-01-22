#ifndef DS3232_C
#define	DS3232_C
//------------------------------------------------------------------------------
#include "ds3232.h"
//------------------------------------------------------------------------------
void ds3232_init(void)
{
	i2c_init();
}
//------------------------------------------------------------------------------
//   Set sec, min, hour, week day (1-7), month day (1-31), month (1-12), year 
//------------------------------------------------------------------------------
void ds3232_setDateTime(uint8_t time[])
{	
  i2c_start();
  
  i2c_write(0xD0);
  i2c_write(WR);
	for(uint8_t i = 0; i < 7; i++)
	{
		i2c_write(get_BCDTime(time[i])); 
	}
  
  i2c_stop();
}
//------------------------------------------------------------------------------
//   Get sec, min, hour, week day (1-7), month day (1-31), month (1-12), year 
//------------------------------------------------------------------------------
void ds3232_getDateTime(uint8_t time[])
{	
  i2c_start();
   
  i2c_write(0xD0); 
  i2c_write(WR);    
  i2c_restart();
  i2c_write(0xD1);                              //Initialize _data reception  
	for(uint8_t i = 0; i < 6; i++)
	{
		time[i] = get_DecTime(i2c_read(ACK));
	}
  time[6] = get_DecTime(i2c_read(NACK));        //Get year & Signal the end of reception
   
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t ds3232_read(uint8_t address)
{
	uint8_t data_;
	
  i2c_start();
   
  i2c_write(0xD0); 
  i2c_write(address);    
  i2c_restart();
  i2c_write(0xD1);                                
  data_ = i2c_read(NACK);        
   
  i2c_stop();
	
	return data_;
}
//------------------------------------------------------------------------------
uint16_t ds3232_getRawTemp(void)
{
	uint16_t data_[2];
	
	data_[0] = ds3232_read(tempLSB_REG);
	data_[1] = ds3232_read(tempMSB_REG);
	
	return (data_[1] << 8) | data_[0];
}
//------------------------------------------------------------------------------
float ds3232_getTemp(void)
{	
	uint16_t rawTemp = ds3232_getRawTemp();
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