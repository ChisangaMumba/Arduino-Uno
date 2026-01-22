//----------------------------------------------------------------------------------
#include "assets/dht22/dht22.c"
#include "assets/lcd8/lcd8.c"
//----------------------------------------------------------------------------------
uint8_t str[18], numStr[10], sensorData[5];
dht22_t sensor;
//----------------------------------------------------------------------------------
void setup(void) 
{
  lcd_init();
}
//----------------------------------------------------------------------------------
void loop(void) 
{
  uint8_t ok = dht22_getSensorData(sensorData);
  
  if(ok == 1 && dht22_isDataValid(sensorData) == 1)
  {
    dht22_setFields(&sensor, sensorData);
      
    dtostrf(sensor.humidity, 6, 1, numStr);   // 6 chars min total width, 1 after decimal point    
    sprintf(str, "Humd:%s%c", numStr, '%');
    lcd_string(0, 0, str);
    
    dtostrf(sensor.temperature, 5, 1, numStr); 
    sprintf(str, "Tempr:%s°C", numStr);
    lcd_string(1, 0, str);
  }
  else
      {
        lcd_string(0, 0, "Error");
      }

  delay(100);
}
//----------------------------------------------------------------------------------