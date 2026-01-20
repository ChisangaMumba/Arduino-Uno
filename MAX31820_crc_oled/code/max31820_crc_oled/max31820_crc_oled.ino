//-----------------------------------------------------------------------------------
#include "assets/max31820/max31820.c"
#include "assets/ssd1306/ssd1306.c"
//-----------------------------------------------------------------------------------
uint8_t str[65], numStr[12], sensorData[9];
float tempr = 0;
//-----------------------------------------------------------------------------------
void setup()
{
  max31820_init(34, -12, RES_09_BIT);  //High, Low, Resolution

  ssd1306_init();
  ssd1306_print(0, 18, "Max31820 sensor"); 
  ssd1306_print(2,  0, "Thermostat:");
  ssd1306_print(6,  0, "Temperarture:");
}
//-----------------------------------------------------------------------------------
void loop() 
{
  uint8_t ok = max31820_getData(sensorData);

  if(ok == 1 && max31820_isDataValid(sensorData) == 1)
  {   
    sprintf(str, "High: %3i°C", max31820_getTH(sensorData));
    ssd1306_print(3, 0, str);

    sprintf(str, "Low:  %3i°C", max31820_getTL(sensorData));
    ssd1306_print(4, 0, str);
    
    tempr = max31820_getTempr(sensorData);
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