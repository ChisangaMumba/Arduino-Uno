//------------------------------------------------------------------------------
#include "assets/bme280/bme280.c"
#include "assets/ht16k33/ht16k33.c"
//------------------------------------------------------------------------------
float temp, pres, hum; // Variables to hold temperature, pressure, and humidity values
uint8_t str[12];
calib_coefs calib;    // Calibration coefficients structure
//------------------------------------------------------------------------------
void setup(void) 
{
  ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
  bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode
}
//------------------------------------------------------------------------------
void loop(void)
{
  temp = bme280_getTemp(calib); // Get temperature in Celsius
  pres = bme280_getPres(calib); // Get pressure in hPa
  hum = bme280_getHum(calib);   // Get humidity in %

  // dtostrf(pres, 6, 1, str);     // 6 chars min total width, 1 after decimal point
  // strcat(str, "hPa");
  // ht16k33_displayText(str);

  dtostrf(temp, 7, 1, str);   
  strcat(str, "°C");
  ht16k33_displayText(str);

  // dtostrf(hum, 8, 1, str);   
  // strcat(str, "%");
  // ht16k33_displayText(str);
  
  delay(100);
}
//------------------------------------------------------------------------------