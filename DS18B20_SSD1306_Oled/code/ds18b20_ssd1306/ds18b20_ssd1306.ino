//-----------------------------------------------------------------------------------
#include "assets/ds18b20/ds18b20.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
void setup()
{
  ssd1306_init();

  ssd1306_print(0, 18, "ds18b20 sensor"); 
  ssd1306_print(3, 28, "Temperature:");
}
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12];
unsigned int rawTemp = 0;
float tempr = 0;
//-----------------------------------------------------------------------------------
void loop() 
{
  if(ds18b20_read(&rawTemp))
  {
    tempr = ds18b20_toFloat(rawTemp);

    dtostrf(tempr, 8, 4, numStr);   // 8 chars min total width, 4 after decimal point
    sprintf(str, "%s°C", numStr);
    ssd1306_print(5, 30, str);;
  }
  else
      {
        ssd1306_print(5, 50, "Error"); 
      }
}
//-----------------------------------------------------------------------------------