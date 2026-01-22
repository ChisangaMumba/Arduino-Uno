//------------------------------------------------------------------------------
#include "assets/bme280/bme280.c"
#include "assets/max7219/max7219.c"
//------------------------------------------------------------------------------
float temp, pres, hum; // Variables to hold temperature, pressure, and humidity values
char str[12];
bme280_calib_coefs calib; // Calibration coefficients structure
//------------------------------------------------------------------------------
void setup(void) 
{
  max7219_init(SCAN_ALL_DIGITS);    
  bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode
}
//------------------------------------------------------------------------------
void loop(void) 
{  
  temp = bme280_getTemp(calib); // Get temperature in Celsius
  // pres = bme280_getPres(calib); // Get pressure in hPa
  // hum = bme280_getHum(calib);   // Get humidity in %
  
  // dtostrf(pres, 6, 1, str);     // 6 chars min total width, 1 after decimal point
  // strcat(str, "hPa");
  // max7219_displayText(str);

  dtostrf(temp, 7, 1, str);   
  strcat(str, "°C");
  max7219_displayText(str);

  // dtostrf(hum, 7, 1, str);   
  // strcat(str, "rh");            //rh: relative humidity
  // max7219_displayText(str);

  delay(100); 
}
//------------------------------------------------------------------------------