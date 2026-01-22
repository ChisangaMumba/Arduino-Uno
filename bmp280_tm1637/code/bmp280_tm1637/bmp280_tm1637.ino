//------------------------------------------------------------------------------
#include "assets/bmp280/bmp280.c"
#include "assets/tm1637/tm1637.c"
//------------------------------------------------------------------------------
uint8_t str[12];
bmp280_calib_coefs calib; // Calibration coefficients structure
//------------------------------------------------------------------------------
void setup(void) 
{
  tm1637_init(8);   // Initialize tm1637 with brightness level 8 (max brightness)
  bmp280_init(&calib, osrs_t_x1, osrs_p_skip, normal_mode); // Initialize BMP280 with 1x oversampling for temperature and skip pressure measurement in normal mode
}
//------------------------------------------------------------------------------
void loop(void)
{
  dtostrf(bmp280_getTemp(calib), 5, 1, str);   
  strcat(str, "°C");
  tm1637_displayText(str);

  delay(100); 
}
//------------------------------------------------------------------------------