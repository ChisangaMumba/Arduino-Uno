//------------------------------------------------------------------------------
#include "assets/dht11.c"
//------------------------------------------------------------------------------
unsigned char sensorData[5];
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
        
        Serial.print(hum);
        Serial.print("%, ");

        Serial.print(tempr);
        Serial.println("C");
      } 
}
//------------------------------------------------------------------------------