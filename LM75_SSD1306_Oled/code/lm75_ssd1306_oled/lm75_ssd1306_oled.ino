//-----------------------------------------------------------------------------------
#include "assets/lm75/lm75.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12];
//-----------------------------------------------------------------------------------
void setup()
{
  lm75_init(32, 25);  //High, Low

  ssd1306_init();
  ssd1306_print(0, 18, "lm75 sensor"); 
  ssd1306_print(2,  0, "Thermostat:");
  ssd1306_print(6,  0, "Temperarture:");
}
//-----------------------------------------------------------------------------------
void loop() 
{ 
  dtostrf(lm75_getTemp(TOS_REG), 5, 1, numStr);   // 5 chars min total width, 1 after decimal point
  sprintf(str, "High: %s°C", numStr);
  ssd1306_print(3, 0, str);

  dtostrf(lm75_getTemp(THYST_REG), 5, 1, numStr); 
  sprintf(str, "Low:  %s°C", numStr);
  ssd1306_print(4, 0, str);

  dtostrf(lm75_getTemp(TEMP_REG), 5, 1, numStr); 
  
  sprintf(str, "Value: %s°C", numStr);
  ssd1306_print(7, 0, str);
}
//-----------------------------------------------------------------------------------