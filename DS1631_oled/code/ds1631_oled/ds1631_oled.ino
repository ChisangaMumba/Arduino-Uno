//-----------------------------------------------------------------------------------
#include "assets/ds1631/ds1631.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12];
//-----------------------------------------------------------------------------------
void setup()
{
  ssd1306_init();
  ds1631_init(24, 20, RES09_BIT);  //High, Low, Resolution
 
  ssd1306_print(0, 28, "ds1631 sensor"); 
  ssd1306_print(2,  0, "Thermostat:");
  ssd1306_print(6,  0, "Temperarture:");
  
  // Thermometer High
  dtostrf(ds1631_getTemp(TH_REG), 5, 1, numStr);  // 5 chars min total width, 1 after decimal point
  sprintf(str, "High: %s°C", numStr);
  ssd1306_print(3, 0, str);
  
  // Thermometer Low
  dtostrf(ds1631_getTemp(TL_REG), 5, 1, numStr);  
  sprintf(str, "Low:  %s°C", numStr);
  ssd1306_print(4, 0, str);
}
//-----------------------------------------------------------------------------------
void loop() 
{    
  // Temperature
  dtostrf(ds1631_getTemp(TEMP_REG), 5, 1, numStr);
  sprintf(str, "Value: %s°C", numStr);
  ssd1306_print(7, 0, str);

  ds1631_convDelay();
}
//-----------------------------------------------------------------------------------