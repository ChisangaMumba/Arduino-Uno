//-----------------------------------------------------------------------------------
#include "assets/dht22/dht22.c"
#include "assets/tm1637/tm1637.c"
//-----------------------------------------------------------------------------------
uint8_t sensorData[5], str[10], numStr[10];
int16_t hum, tempr;
//-----------------------------------------------------------------------------------
void setup(void)
{
  tm1637_init(8);   // Initialize TM1637 with maximum brightness
}
//-----------------------------------------------------------------------------------
void loop(void) 
{
  // tm1637_displayNumText(" 287");
  oneWire_start();
  
  if(oneWire_getResponse())
  {	
    dht22_getSensorData(sensorData);
  }
  
  if(dht22_isChecksumInvalid(sensorData))
  {
    tm1637_write(" Err");
  }
  else
      {
        tempr = dht22_getTemperature(sensorData); 
        dtostrf(calcTempr(tempr), 5, 1, numStr);   // 5 chars min total width, 1 after decimal point               
        
        tm1637_displayNumText(numStr);
      } 
}
//-----------------------------------------------------------------------------------