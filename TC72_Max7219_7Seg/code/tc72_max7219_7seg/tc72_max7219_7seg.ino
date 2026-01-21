//-----------------------------------------------------------------------------------
#include "assets/max7219/max7219.c"
#include "assets/tc72/tc72.c"
#include <stdio.h>
//-----------------------------------------------------------------------------------
float tempr;
uint8_t str[12]; // Buffer for temperature string, enough for "99999.99°C" + null terminator
//-----------------------------------------------------------------------------------
void setup(void)
{
  max7219_init(SCAN_ALL_DIGITS);
  tc72_init();
}
//-----------------------------------------------------------------------------------
void loop(void)
{
  tempr = tc72_getTempr2();
  
  // Convert temperature to string format
  dtostrf(tempr, 7, 2, str); // 7 chars min total width, 2 after decimal point
  
  strcat(str, "°C");  

  max7219_displayText(str);
}
//-----------------------------------------------------------------------------------