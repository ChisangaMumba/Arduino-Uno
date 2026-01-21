//------------------------------------------------------------------------------
#include "assets/bmp280/bmp280.c"
#include "assets/ht16k33/ht16k33.c"
//------------------------------------------------------------------------------
uint8_t str[12];
bmp280_calib_coefs calib; // Calibration coefficients structure
//------------------------------------------------------------------------------
void setup(void) 
{
  ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
  bmp280_init(&calib, osrs_t_x1, osrs_p_skip, normal_mode); // Initialize BMP280 with 1x oversampling for temperature and skip pressure measurement in normal mode
}
//------------------------------------------------------------------------------
void loop(void)
{
  // dtostrf(bmp280_getPres(calib), 6, 1, str);     // 7 chars min total width, 2 after decimal point
  // strcat(str, "hPa");
  // ht16k33_displayText(str);

  dtostrf(bmp280_getTemp(calib), 7, 1, str);   
  strcat(str, "°C");
  ht16k33_displayText(str);
}
//------------------------------------------------------------------------------