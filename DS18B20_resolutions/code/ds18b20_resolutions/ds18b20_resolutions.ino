//-----------------------------------------------------------------------------------
#include "assets/ds18b20/ds18b20.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
void setup()
{
  ds18b20_init(29, -15, RES_09_BIT);  //High, Low, Resolution

  ssd1306_init();
  ssd1306_print(0, 18, "ds18b20 sensor"); 
  ssd1306_print(2,  0, "Thermostat:");
  ssd1306_print(6,  0, "Temperarture:");
}
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12], sensorData[9];
float tempr = 0;
//-----------------------------------------------------------------------------------
void loop() 
{
  if( ds18b20_getData(sensorData) )
  {   
    sprintf(str, "High: %3i°C", ds18b20_getTH(sensorData));
    ssd1306_print(3, 0, str);

    sprintf(str, "Low:  %3i°C", ds18b20_getTL(sensorData));
    ssd1306_print(4, 0, str);
    
    tempr = ds18b20_getTempr(sensorData);
    dtostrf(tempr, 8, 1, numStr);   // 8 chars min total width, 1 after decimal point
    
    sprintf(str, "%s°C", numStr);
    ssd1306_print(7, 0, str);
  }
  else
      {
        ssd1306_print(3, 50, "Error"); 
      }
}
//-----------------------------------------------------------------------------------