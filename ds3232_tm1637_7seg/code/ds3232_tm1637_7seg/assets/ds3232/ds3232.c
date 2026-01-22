#ifndef DS3232_C
#define	DS3232_C
//------------------------------------------------------------------------------
#include "ds3232.h"
//------------------------------------------------------------------------------
void ds3232_init(uint8_t time[])
{
	i2c_init();

  // uncomment the next line if you want to set the initial date and time
  // ds3232_setDateTime(time); // Set initial date and time
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
void ds3232_getDateTime(time_t *tm, uint8_t time[])
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

  ds3232_setDateTimeObj(tm, time); // Set the time structure with the received time data
}
//------------------------------------------------------------------------------
uint8_t ds3232_read(uint8_t address)
{
  uint8_t data;
	
  i2c_start();
   
  i2c_write(0xD0); 
  i2c_write(address);    
  i2c_restart();
  i2c_write(0xD1);                                
  data = i2c_read(NACK);        
   
  i2c_stop();
	
  return data;
}
//------------------------------------------------------------------------------
void ds3232_setDateTimeObj(time_t *tm, uint8_t time[])
{
  tm->second = time[0]; 
  tm->minute = time[1]; 
  tm->hour = time[2];  
  tm->dayOfWeek = time[3];  // Day of the week (1-7)
  tm->dayOfMonth = time[4]; // Day of the month (1-31)
  tm->month = time[5];      // Month (1-12)
  tm->year = time[6];       // Year two digits (e.g., 23 for 2023)
  
  if(tm->isColonOn)
    sprintf(tm->time, "%02d.%02d.", tm->hour, tm->minute);    // Format time as HH:MM:
  else
    sprintf(tm->time, "%02d%02d", tm->hour, tm->minute);      // Format time as HHMM
  tm->isColonOn = !tm->isColonOn;		// Toggle Colon state

  sprintf(tm->date, "%02d.%02d.", tm->dayOfMonth, tm->month); // Format date as DD.MM
}
//------------------------------------------------------------------------------
//  Optional temperature reading functions
//------------------------------------------------------------------------------
uint16_t ds3232_getRawTemp(void)
{
  uint16_t data[2];
	
  data[0] = ds3232_read(tempLSB_REG);
  data[1] = ds3232_read(tempMSB_REG);
	
  return (data[1] << 8) | data[0];
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