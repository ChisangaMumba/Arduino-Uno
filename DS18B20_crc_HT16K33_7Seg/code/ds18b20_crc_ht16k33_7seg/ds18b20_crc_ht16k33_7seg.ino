//-----------------------------------------------------------------------------------
#include "assets/ds18b20/ds18b20.c"
#include "assets/ht16k33/ht16k33.c"
//-----------------------------------------------------------------------------------
float tempr = 0;
uint8_t str[12], sensorData[9];
//-----------------------------------------------------------------------------------
void setup()
{
  ht16k33_init(15);  // Initialize HT16K33 with brightness level 15 
  ds18b20_init(34, -12, RES_10_BIT);  //Thermostat: High, Low, and Resolution
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
    ht16k33_displayText(str);
  }
  else
      {
        ht16k33_displayText("Error  "); 
      }
}
//-----------------------------------------------------------------------------------