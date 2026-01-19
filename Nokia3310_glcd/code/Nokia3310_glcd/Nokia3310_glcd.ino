//------------------------------------------------------------------------------
#include "assets/dht22.c"
#include "assets/nokia/nokia_glcd.c"
//------------------------------------------------------------------------------
uint8_t sensorData[5];
int hum, tempr;
char str[18], numStr[18];
//------------------------------------------------------------------------------
void setup() 
{
  LCD_init();
  //LCD_image(img);
  LCD_string(0, 2, "Nokia 3310");
  LCD_string(2, 5, "DHT22");
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
    LCD_string(0, 2, "Error");
  }
  else
      {
        hum = dht22_getHumidity(sensorData);
        tempr = dht22_getTemperature(sensorData);
        
        dtostrf((float)hum/10, 6, 1, numStr);   // 6 chars min total width, 1 after decimal point
        sprintf(str, "Humd: %s%c", numStr, '%');  
        LCD_string(4, 0, str);

        dtostrf(calcTempr(tempr), 6, 1, numStr);   
        sprintf(str, "Temp: %s°C", numStr);  
        LCD_string(5, 0, str);
      } 
}
//------------------------------------------------------------------------------