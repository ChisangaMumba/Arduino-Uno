//-----------------------------------------------------------------------------------
#include "assets/ds182x/ds182x.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12], sensorData[9];
float tempr = 0;
//-----------------------------------------------------------------------------------
void setup()
{
  ssd1306_init();
  ds182x_init(34, 25, RES_09_BIT);  // High, Low, Resolution

  ssd1306_print(0, 18, "DS18EA00 sensor"); 
  ssd1306_print(2,  0, "Thermostat:");
  ssd1306_print(6,  0, "Temperarture:");
}
//-----------------------------------------------------------------------------------
void loop() 
{
  uint8_t ok = ds182x_getData(sensorData);

  if(ok == 1 && ds182x_isDataValid(sensorData, 8) == 1)
  {   
    sprintf(str, "High: %3i°C", ds182x_getTH(sensorData));
    ssd1306_print(3, 0, str);

    sprintf(str, "Low:  %3i°C", ds182x_getTL(sensorData));
    ssd1306_print(4, 0, str);
    
    tempr = ds182x_getTempr(sensorData);
    dtostrf(tempr, 5, 1, numStr);           // 5 chars min total width, 1 after decimal point
    
    sprintf(str, "Value: %s°C", numStr);
    ssd1306_print(7, 0, str);
  }
  else
      {
        ssd1306_print(3, 50, "Error"); 
      }
}
//-----------------------------------------------------------------------------------