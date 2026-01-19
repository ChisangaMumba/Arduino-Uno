//-----------------------------------------------------------------------------------
#include "assets/dht11/dht11.c"
#include "assets/ht16k33/ht16k33.c"
//-----------------------------------------------------------------------------------
void setup()
{
  ht16k33_init();
}
//-----------------------------------------------------------------------------------
uint8_t sensorData[5], str[10];
int16_t hum, tempr;
//-----------------------------------------------------------------------------------
void loop() 
{
  oneWire_start();
  
  if(oneWire_getResponse())
  {	
    dht11_getSensorData(sensorData);
  }
  
  if(dht11_isChecksumInvalid(sensorData))
  {
    Serial.println("Error");
  }
  else
      {
        hum = dht11_getHumidity(sensorData);
        tempr = dht11_getTemperature(sensorData);

        sprintf(str, "%2u%c%3u°%c", hum, '%', tempr, 'C');            
        ht16k33_displayText(str);
      } 
}
//-----------------------------------------------------------------------------------