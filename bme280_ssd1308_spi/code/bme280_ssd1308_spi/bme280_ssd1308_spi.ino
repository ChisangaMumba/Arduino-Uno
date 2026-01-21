//------------------------------------------------------------------------------
#include "assets/bme280/bme280.c"
#include "assets/ssd1308/ssd1308.c"
//------------------------------------------------------------------------------
char str[65], numStr[12];
bme280_calib_coefs calib; // Calibration coefficients structure
//------------------------------------------------------------------------------
void setup(void) 
{
  ssd1308_init();    
  bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode

  ssd1308_print(0, 27, "Bme280 sensor");
	ssd1308_print(2, 32, "SPI Mode:");
}
//------------------------------------------------------------------------------
void loop(void) 
{  
  dtostrf(bme280_getPres(calib), 7, 2, numStr);     // 7 chars min total width, 2 after decimal point
  sprintf(str, "Pres: %shPa", numStr);
  ssd1308_print(4, 0, str);

  dtostrf(bme280_getTemp(calib), 5, 1, numStr);   
  sprintf(str, "Temp: %s°C", numStr);
  ssd1308_print(5, 0, str);

  dtostrf(bme280_getHum(calib), 7, 1, numStr);   
  sprintf(str, "Humd: %s%c", numStr, '%');
  ssd1308_print(6, 0, str);

  delay(100); 
}
//------------------------------------------------------------------------------