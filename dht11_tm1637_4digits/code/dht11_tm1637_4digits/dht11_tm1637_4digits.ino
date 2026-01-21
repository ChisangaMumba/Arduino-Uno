//-----------------------------------------------------------------------------------
#include "assets/dht11/dht11.c"
#include "assets/tm1637/tm1637.c"
//-----------------------------------------------------------------------------------
uint8_t sensorData[5], str[12];
int16_t hum, tempr;
//-----------------------------------------------------------------------------------
void setup(void)
{
  tm1637_init(8);   // Initialize TM1637 with maximum brightness
}
//-----------------------------------------------------------------------------------
void loop(void) 
{
  oneWire_start();
  
  if(oneWire_getResponse())
  {	
    dht11_getSensorData(sensorData);
  }
  
  if(dht11_isChecksumInvalid(sensorData))
  {
    tm1637_write(" Err");
  }
  else
      {
        tempr = dht11_getTemperature(sensorData);            
        sprintf(str, "%2u°c", tempr); // Format temperature string  0 - 50°c      
        
        tm1637_displayNumText(str);
      } 
}
//-----------------------------------------------------------------------------------