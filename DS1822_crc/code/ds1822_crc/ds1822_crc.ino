//-----------------------------------------------------------------------------------
#include "assets/ds1822/ds1822.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12], sensorData[9];
float tempr = 0;
//-----------------------------------------------------------------------------------
void setup()
{
  ds1822_init(34, 25, RES_09_BIT);  //High, Low, Resolution

  ssd1306_init();
  ssd1306_print(0, 18, "DS1822 sensor"); 
  ssd1306_print(2,  0, "Thermostat:");
  ssd1306_print(6,  0, "Temperarture:");
}
//-----------------------------------------------------------------------------------
void loop() 
{
  uint8_t ok = ds1822_getData(sensorData);

  if(ok == 1 && ds1822_isDataValid(sensorData, 8) == 1)
  {   
    sprintf(str, "High: %3i°C", ds1822_getTH(sensorData));
    ssd1306_print(3, 0, str);

    sprintf(str, "Low:  %3i°C", ds1822_getTL(sensorData));
    ssd1306_print(4, 0, str);
    
    tempr = ds1822_getTempr(sensorData);
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