//-----------------------------------------------------------------------------------
#include "assets/HTU21/HTU21.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12];
//-----------------------------------------------------------------------------------
void setup()
{
  ssd1306_init();
  HTU21_init(RES_0);

  ssd1306_print(0, 30, "HTU21 sensor"); 
  ssd1306_print(4,  0, "Readings:");
  sprintf(str, "Config: 0x%x", HTU21_readConfig());
	ssd1306_print(2, 0, str);
}
//-----------------------------------------------------------------------------------
void loop() 
{
  dtostrf(HTU21_getHumd(), 7, 2, numStr);  // 7 chars min total width, 2 after decimal point
  sprintf(str, "Humd:%s%c", numStr, '%');
  ssd1306_print(5, 0, str);
  
  dtostrf(HTU21_getTemp(), 7, 2, numStr);           
  sprintf(str, "Temp:%s°C", numStr);
  ssd1306_print(6, 0, str);

  delay(100);
}
//-----------------------------------------------------------------------------------