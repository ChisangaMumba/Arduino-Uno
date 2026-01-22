//------------------------------------------------------------------------------
#include "assets/bmp280/bmp280.c"
#include "assets/max7219/max7219.c"
//------------------------------------------------------------------------------
float press, temp;
char str[12];
bmp280_calib_coefs calib; // Calibration coefficients structure
//------------------------------------------------------------------------------
void setup(void) 
{
  max7219_init(SCAN_ALL_DIGITS);
  bmp280_init(&calib, osrs_t_x1, osrs_p_x1, normal_mode);  // Initialize BMP280 with 1x oversampling for temperature and pressure, normal mode
}
//------------------------------------------------------------------------------
void loop(void) 
{  
  temp = bmp280_getTemp(calib);   // Get temperature in Celsius 
  press = bmp280_getPres(calib);  // Get pressure in hPa

  // dtostrf(press, 6, 1, str);      // 6 chars min total width, 1 after decimal point
  // strcat(str, "hPa");
  // max7219_displayText(str);

  dtostrf(temp, 7, 1, str);   // 7 chars min total width, 1 after decimal point
  strcat(str, "°C");
  max7219_displayText(str);

  delay(100); 
}
//------------------------------------------------------------------------------