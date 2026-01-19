//-----------------------------------------------------------------------------------
#include "assets/lm75/LM75.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
void setup()
{
  LM75_init();
  ssd1306_init();

  ssd1306_print(0, 27, "SSD1306 OLED"); 
  ssd1306_print(3, 28, "Temperature:");
}
//-----------------------------------------------------------------------------------
uint8_t str[10], numStr[10];
void loop() 
{
  dtostrf(LM75_read(TEMPERATURE_ADDRESS), 7, 1, numStr);   // 7 chars min total width, 1 after decimal point
  sprintf(str, "%s°C", numStr);    
  
  ssd1306_print(5, 27, str);
}
//-----------------------------------------------------------------------------------