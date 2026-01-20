//-----------------------------------------------------------------------------------
#include "assets/si7021/si7021.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12];
uint16_t rawTemp, rawHumd;
//-----------------------------------------------------------------------------------
void setup()
{
  SI7021_init(RES_0);

  ssd1306_init();
  ssd1306_print(0, 30, "SI7021 sensor"); 
  ssd1306_print(4,  0, "Readings:");
  sprintf(str, "Config: 0x%x", SI7021_readConfig());
	ssd1306_print(2, 0, str);
}
//-----------------------------------------------------------------------------------
void loop() 
{
  rawHumd = SI7021_readConv(HUMD_NO_HOLD_CMD);
  rawTemp = SI7021_readConv(TEMP_NO_HOLD_CMD);

  if(rawHumd != 0xFFFF)
  {
    dtostrf(SI7021_calcHumd(rawHumd), 7, 2, numStr);  // 7 chars min total width, 2 after decimal point
    sprintf(str, "Humd:%s%c", numStr, '%');
    ssd1306_print(5, 0, str);
  }

  if(rawTemp != 0xFFFF)
  {
    dtostrf(SI7021_calcTemp(rawTemp), 7, 2, numStr);           
    sprintf(str, "Temp:%s°C", numStr);
    ssd1306_print(6, 0, str);
  }  

  delay(100);
}
//-----------------------------------------------------------------------------------