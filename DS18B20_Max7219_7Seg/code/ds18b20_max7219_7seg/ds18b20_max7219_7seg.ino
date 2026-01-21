//-----------------------------------------------------------------------------------
#include "assets/max7219/max7219.c"
#include "assets/ds18b20/ds18b20.c"
//-----------------------------------------------------------------------------------
float tempr;
uint8_t str[12], sensorData[9];  
//-----------------------------------------------------------------------------------
void setup()
{
  max7219_init(SCAN_ALL_DIGITS);
  ds18b20_init(32, 20, RES_10_BIT);  //Thermostat: High, Low, Resolution
}
//-----------------------------------------------------------------------------------
void loop() 
{
  uint8_t ok = ds18b20_getData(sensorData);

  if(ok == 1 && ds18b20_isDataValid(sensorData, 8) == 1)
  {       
    tempr = ds18b20_getTempr(sensorData);
    dtostrf(tempr, 7, 2, str);           // 7 chars min total width, 2 after decimal point
    
    strcat(str, "°C");
    max7219_displayText(str);
  }
  else
      {
        max7219_displayText("Error  "); 
      }
}
//-----------------------------------------------------------------------------------