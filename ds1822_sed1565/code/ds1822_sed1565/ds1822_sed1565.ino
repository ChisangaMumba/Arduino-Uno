//----------------------------------------------------------------------------------
#include "assets/ds1822/ds1822.c"
#include "assets/sed1565/sed1565.c"
//----------------------------------------------------------------------------------
uint8_t str[34], numStr[12], sensorData[9];
ds1822_t sensor;
//----------------------------------------------------------------------------------
void setup(void) 
{
	sed1565_init();
	ds1822_init(13, -5, RES_09_BIT);  //High, Low, Resolution

	sed1565_print(0, 30, "DS1822 sensor");
	sed1565_print(2, 0,  "Thermostat");
	sed1565_print(6, 0,  "Temperature");
}
//----------------------------------------------------------------------------------
void loop(void) 
{
	uint8_t ok = ds1822_getData(sensorData);

	if(ok == 1 && ds1822_isDataValid(sensorData, 8) == 1)
	{
		ds1822_setFields(&sensor, sensorData);

		sprintf(str, "High:%3i°C", sensor.tempHigh);
		sed1565_print(3, 0, str);
	
		sprintf(str, "Low:%4i°C", sensor.tempLow);
		sed1565_print(4, 0, str);
	
		dtostrf(sensor.temperature, 5, 1, numStr); // 5 chars min total width, 1 after decimal point
		sprintf(str, "Value: %s°C", numStr);
		sed1565_print(7, 0, str);

		ds1822_convDelay(sensor.resIndex); // wait for conversion to complete
	}
	else
		{
			sed1565_print(3, 0, "DS1822 Error");
			sed1565_print(7, 0, "DS1822 Error");
		}
}
//----------------------------------------------------------------------------------