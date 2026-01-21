//-----------------------------------------------------------------------------------
#include "assets/bmp180/bmp180.c"
#include "assets/ht16k33/ht16k33.c"
//-----------------------------------------------------------------------------------
float press, temp;
uint8_t str[15];
//-----------------------------------------------------------------------------------
void setup(void)
{
  ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
  bmp180_init();
}
//-----------------------------------------------------------------------------------
void loop(void) 
{ 
  temp = bmp180_getTemp();   // always read temperature first, needed for pressure calculation
  // press = bmp180_getPress();   // Uncomment this line if you want to read pressure

  // dtostrf(press, 6, 1, str);   // 5 chars min total width, 1 after decimal point
  // strcat(str, "hPa");
  // ht16k33_displayText(str);
  
  dtostrf(temp, 7, 1, str);   // 5 chars min total width, 1 after decimal point
  strcat(str, "°C");
  ht16k33_displayText(str);
}
//-----------------------------------------------------------------------------------