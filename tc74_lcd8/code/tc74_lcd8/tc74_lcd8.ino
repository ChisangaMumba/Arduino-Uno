//----------------------------------------------------------------------------------
#include "assets/tc74/tc74.c"
#include "assets/lcd8/lcd8.c"
//----------------------------------------------------------------------------------
uint8_t str[16];  // Buffer for the temperature string.
//----------------------------------------------------------------------------------
void setup(void) 
{
  lcd_init();
  tc74_init(NORMAL_MODE);  // Initialize TC74 with normal mode.

  lcd_string(0, 3, "TC74 Sensor");
}
//----------------------------------------------------------------------------------
void loop(void) 
{
  sprintf(str, "Temp:%4i°C", tc74_readTemp());  // Read temperature and format it as a string.
  
  lcd_string(1, 0, str);  // Display temperature on the second row of the LCD.
}
//----------------------------------------------------------------------------------