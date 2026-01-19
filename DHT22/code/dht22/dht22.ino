//------------------------------------------------------------------------------
#include "assets/dht22.c"
//------------------------------------------------------------------------------
uint8_t sensorData[5];
int hum, tempr;
//------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(9600);
}
//------------------------------------------------------------------------------
void loop() 
{
  oneWire_start();
  
  if(oneWire_getResponse())
  {	
    dht22_getSensorData(sensorData);
  }
  
  if(dht22_isChecksumInvalid(sensorData))
  {
    Serial.println("Error");
  }
  else
      {
        hum = dht22_getHumidity(sensorData);
        tempr = dht22_getTemperature(sensorData);
        
        Serial.print((float) hum/10, 1);
        Serial.print("%, ");

        Serial.print(calcTempr(tempr), 1);
        Serial.println("C");
      } 
}
//------------------------------------------------------------------------------