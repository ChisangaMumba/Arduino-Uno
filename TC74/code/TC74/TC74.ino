//-----------------------------------------------------------------------------------
#include "assets/tc74/tc74.c"
#include "assets/lcd/LCD_Serial.c"
//-----------------------------------------------------------------------------------
void setup()
{
  LCD_init();
  LCD_string(0, 3, "TC74 Sensor");

  TC74_init(NORMAL_MODE);						// NORMAL vs STANDBY mode
}
//-----------------------------------------------------------------------------------
uint8_t str[18];
int8_t tempr = 0;
void loop() 
{
  tempr = TC74_read(TEMPR_REG);
  sprintf(str, "Temp: %3i°C", tempr);  

  LCD_string(1, 1, str);
}
//-----------------------------------------------------------------------------------