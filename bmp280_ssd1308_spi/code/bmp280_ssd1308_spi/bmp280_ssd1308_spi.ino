//------------------------------------------------------------------------------
#include "assets/bmp280/bmp280.c"
#include "assets/ssd1308/ssd1308.c"
//------------------------------------------------------------------------------
char str[65], numStr[12];
bmp280_calib_coefs calib; // Calibration coefficients structure
//------------------------------------------------------------------------------
void setup(void) 
{
  ssd1308_init();    
  bmp280_init(&calib, osrs_t_x1, osrs_p_x1, normal_mode); // Initialize BMP280 with 1x oversampling for both temperature and pressure in normal mode

  ssd1308_print(0, 27, "BMP280 sensor");
	ssd1308_print(2, 32, "SPI Mode:");
}
//------------------------------------------------------------------------------
void loop(void) 
{  
  dtostrf(bmp280_getPres(calib), 7, 2, numStr);     // 7 chars min total width, 2 after decimal point
  sprintf(str, "Pres: %shPa", numStr);
  ssd1308_print(4, 0, str);

  dtostrf(bmp280_getTemp(calib), 5, 1, numStr);   
  sprintf(str, "Temp: %s°C", numStr);
  ssd1308_print(5, 0, str);

  delay(100); 
}
//------------------------------------------------------------------------------