//-----------------------------------------------------------------------------------
#include "assets/th02/th02.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12];
//-----------------------------------------------------------------------------------
void setup()
{
  TH02_init();

  ssd1306_init();
  ssd1306_print(0, 30, "TH02 sensor"); 
  ssd1306_print(4,  0, "Readings:");
  sprintf(str, "Device ID: 0x%x", TH02_readDevice(DEV_ID_REG));
	ssd1306_print(2, 0, str);
}
//-----------------------------------------------------------------------------------
void loop() 
{
  dtostrf(TH02_getHumd(), 7, 2, numStr);  // 7 chars min total width, 2 after decimal point
  sprintf(str, "Humd:%s%c", numStr, '%');
  ssd1306_print(5, 0, str);
  
  dtostrf(TH02_getTemp(), 7, 2, numStr);           
  sprintf(str, "Temp:%s°C", numStr);
  ssd1306_print(6, 0, str);

  delay(100);
}
//-----------------------------------------------------------------------------------