//----------------------------------------------------------------------------------
#include "assets/ds18b20/ds18b20.c"
#include "assets/lcd4/lcd4.c"
//----------------------------------------------------------------------------------
uint8_t str[20], numStr[12], sensorData[9];
ds18b20_t sensor;
//----------------------------------------------------------------------------------
void setup(void) 
{
  lcd_init();
  ds18b20_init(34, -15, RES_12_BIT); // Initialize DS18B20 with TH=0, TL=0, resolution=12-bit
}
//----------------------------------------------------------------------------------
void loop(void) 
{
  uint8_t ok = ds18b20_getData(sensorData);
    
  if(ok == 1 && ds18b20_isDataValid(sensorData,8) == 1)
  {   
	  ds18b20_setFields(&sensor, sensorData); // Set fields in sensor struct

    sprintf(str, "H:%3i°C,L:%3i°C", sensor.tempHigh, sensor.tempLow);
    lcd_string(0, 0, str);
    
    dtostrf(sensor.temperature, 8, 4, numStr); // 8 chars min total width, 4 after decimal point
    sprintf(str, "Temp:%s°C", numStr);
	  lcd_string(1, 0, str);

	  ds18b20_convDelay(sensor.resIndex); 		// Wait for conversion based on resolution index
  }
  else
      {
        lcd_string(0, 0, "Error"); 
      }
}
//----------------------------------------------------------------------------------