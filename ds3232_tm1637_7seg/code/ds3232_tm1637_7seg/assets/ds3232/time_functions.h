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
#endif