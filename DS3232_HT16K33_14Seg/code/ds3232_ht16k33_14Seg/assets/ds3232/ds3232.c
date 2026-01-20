#ifndef DS3232_C
#define	DS3232_C
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
#include "Time_functions.h"
//------------------------------------------------------------------------------
#define WR 0
#define RD 1
//------------------------------------------------------------------------------
void ds3232_init()
{
	I2C_init();
}
//---Set sec, min, hour, week day (1-7), month day (1-31), month (1-12), year--- 
void ds3232_setDateTime(uint8_t time[])
{	
  I2C_start();
  
  I2C_write(0xD0);
  I2C_write(WR);
	for(uint8_t i = 0; i < 7; i++)
	{
		I2C_write(get_BCDTime(time[i])); 
	}
  
  I2C_stop();
}
//---Get sec, min, hour, week day (1-7), month day (1-31), month (1-12), year--- 
void ds3232_getDateTime(uint8_t time[])
{	
  I2C_start();
   
  I2C_write(0xD0); 
  I2C_write(WR);    
  I2C_restart();
  I2C_write(0xD1);                              //Initialize _data reception  
	for(uint8_t i = 0; i < 6; i++)
	{
		time[i] = get_DecTime(I2C_read(ACK));
	}
  time[6] = get_DecTime(I2C_read(NACK));        //Get year & Signal the end of reception
   
  I2C_stop();
}
//------------------------------------------------------------------------------
#endif