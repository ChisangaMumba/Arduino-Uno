//------------------------------------------------------------------------------
#include "assets/dht22/dht22.c"
#include "assets/max7219/max7219.c"
//------------------------------------------------------------------------------
uint8_t str[30], numStr[2][10], sensorData[5];
dht22_t sensor;
//------------------------------------------------------------------------------
void setup(void) 
{
  max7219_init(2);    //Number of chips connected in daisy chain
}
//------------------------------------------------------------------------------
void loop(void) 
{  
  uint8_t ok = dht22_getSensorData(sensorData);
  
  if(ok == 1 && dht22_isDataValid(sensorData) == 1)
  {
    dht22_setFields(&sensor, sensorData);
      
    dtostrf(sensor.humidity, 7, 1, numStr[0]);      // 7 chars min total width, 1 after decimal point    
    dtostrf(sensor.temperature, 6, 1, numStr[1]);    
   
    sprintf(str, "%srH %s°C", numStr[0], numStr[1]);
    max7219_displayText(str);
  }
  else
      {
        max7219_displayText("Error");
      }

  delay(100);
}
//------------------------------------------------------------------------------