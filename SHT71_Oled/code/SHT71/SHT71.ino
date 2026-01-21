//------------------------------------------------------------------------------
#include "assets/sht7x/sht7x.c"
#include "assets/ssd1306/ssd1306.c"
//------------------------------------------------------------------------------
uint8_t str[65], numStr[12];
float tempr = 0;
//------------------------------------------------------------------------------
void setup() 
{
  SHT7x_init();
  
  ssd1306_init();
  ssd1306_print(0, 30, "SHT71 sensor"); 
  ssd1306_print(2,  0, "Readings:");
}
//------------------------------------------------------------------------------
void loop()
{
  tempr = SHT7x_getTemp();

  dtostrf(SHT7x_getHumd(tempr), 6, 2, numStr);     // 6 chars min total width, 2 after decimal point
  sprintf(str, "Humd: %s%c", numStr, '%');
  ssd1306_print(4, 0, str);

  dtostrf(tempr, 6, 2, numStr);   
  sprintf(str, "Temp: %s°C", numStr);
  ssd1306_print(5, 0, str);

  delay(100);
}
//------------------------------------------------------------------------------