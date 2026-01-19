//-----------------------------------------------------------------------------------
#include "assets/tm1637/tm1637.c"
#include "assets/ds1620/ds1620.c"
//-----------------------------------------------------------------------------------
void setup()
{
  TM1637_init(7);
  ds1620_init(-10, 30);     // Set thermostat high and low values (entirely optional)
}
//-----------------------------------------------------------------------------------
uint8_t str[10];
int16_t rawTempr = 0;
void loop() 
{
  rawTempr = ds1620_read(READ_TEMPR);
  sprintf(str, "%4i°c", calcTempr(rawTempr));
  TM1637_displayNumText(str);
}
//-----------------------------------------------------------------------------------