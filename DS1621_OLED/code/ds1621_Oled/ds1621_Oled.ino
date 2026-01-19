//-----------------------------------------------------------------------------------
#include "assets/ds1621/ds1621.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
uint8_t addr = 0x90; // Temperature sensor device Address
void setup()
{
  ds1621_init(addr);
  ssd1306_init();
  
  ssd1306_print(0, 20, "DS1621 Sensor"); 
}
//-----------------------------------------------------------------------------------
uint8_t str[30], numStr[30];
int16_t tempr;
void loop() 
{
  tempr = ds1621_read2ByteReg(addr, TEMP_REG);

  dtostrf(toFloat(tempr), 5, 1, numStr);   // 5 chars min total width, 1 after decimal point
  sprintf(str, "Temperature: %s°C", numStr);   
  
  ssd1306_print(2, 0, str);
}
//-----------------------------------------------------------------------------------