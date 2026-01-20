#ifndef TIME_H
#define	TIME_H
//-----------------------Change BCD time to Decimal-----------------------------
uint8_t get_DecTime(uint8_t time)
{   
  return ((time >> 4) * 10) + (time & 0x0F);  
}
//-----------------------Change Decimal time to BCD-----------------------------
uint8_t get_BCDTime(uint8_t time)
{
  return ((time / 10) << 4) + (time % 10);
}
//------------------------------------------------------------------------------
uint8_t* get_TimeStr(uint8_t tm[], uint8_t sepr)
{
  uint8_t timeStr[12];
  
  sprintf(timeStr, "%02d%c%02d%c%02d", tm[2],sepr, tm[1],sepr, tm[0]);  
  
  return timeStr; 
}
//------------------------------------------------------------------------------
uint8_t* get_DateStr(uint8_t tm[], uint8_t sepr)
{
  uint8_t timeStr[12];
  
	sprintf(timeStr, "%02d%c%02d%c%02d", tm[4], sepr, tm[5], sepr, tm[6]); 
	
  return timeStr; 
}
//------------------------------------------------------------------------------
#endif