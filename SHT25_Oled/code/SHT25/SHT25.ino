//------------------------------------------------------------------------------
#include "assets/sht2x/sht2x.c"
#include "assets/ssd1306/ssd1306.c"
//------------------------------------------------------------------------------
uint8_t str[65], numStr[12];
//------------------------------------------------------------------------------
void setup() 
{
  SHT2x_init();
  
  ssd1306_init();
  ssd1306_print(0, 18, "SHT25 sensor"); 
  ssd1306_print(2,  0, "Readings:");
}
//------------------------------------------------------------------------------
void loop()
{
  dtostrf(SHT2x_getHumd(), 6, 2, numStr);     // 6 chars min total width, 2 after decimal point
  sprintf(str, "Humd: %s%c", numStr, '%');
  ssd1306_print(3, 0, str);

  dtostrf(SHT2x_getTemp(), 6, 2, numStr);   
  sprintf(str, "Temp: %s°C", numStr);
  ssd1306_print(4, 0, str);

  delay(100);
}
//------------------------------------------------------------------------------