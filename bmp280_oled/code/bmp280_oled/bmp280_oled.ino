//------------------------------------------------------------------------------
#include "assets/bmp280/bmp280.c"
#include "assets/ssd1306/ssd1306.c"
//------------------------------------------------------------------------------
uint8_t str[65], numStr[12];
bmp280_calib_coefs calib; // Calibration coefficients structure
//------------------------------------------------------------------------------
void setup(void) 
{
  ssd1306_init();
  bmp280_init(&calib, osrs_t_x1, osrs_p_x1, normal_mode); // Initialize BMP280 with 1x oversampling for both temperature and pressure in normal mode
  
  ssd1306_print(0, 30, "BMP280 sensor"); 
  ssd1306_print(2,  0, "Readings:");
}
//------------------------------------------------------------------------------
void loop(void)
{
  dtostrf(bmp280_getPres(calib), 7, 2, numStr);     // 7 chars min total width, 2 after decimal point
  sprintf(str, "Pres: %shPa", numStr);
  ssd1306_print(4, 0, str);

  dtostrf(bmp280_getTemp(calib), 5, 1, numStr);   
  sprintf(str, "Temp: %s°C", numStr);
  ssd1306_print(5, 0, str);

  delay(100);
}
//------------------------------------------------------------------------------