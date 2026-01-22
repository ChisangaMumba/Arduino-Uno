//----------------------------------------------------------------------------------
#include "assets/dht11/dht11.c"
#include "assets/lcd4/lcd4.c"
//----------------------------------------------------------------------------------
uint8_t str[20], sensorData[5];
dht11_t sensor;
//----------------------------------------------------------------------------------
void setup(void) 
{
  lcd_init();
}
//----------------------------------------------------------------------------------
void loop(void) 
{
  uint8_t ok = dht11_getSensorData(sensorData);
    
  if(ok == 1 && dht11_isDataValid(sensorData) == 1)
  {   
	  dht11_setFields(&sensor, sensorData); // Set fields in sensor struct

    sprintf(str, "Humd:%3i%c", sensor.humidity, '%');
    lcd_string(0, 0, str);
    
    sprintf(str, "Temp:%3i°C", sensor.temperature);
	  lcd_string(1, 0, str);
  }
  else
      {
        lcd_string(0, 0, "Error"); 
      }
}
//----------------------------------------------------------------------------------