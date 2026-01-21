//-----------------------------------------------------------------------------------
#include "assets/bmp280/bmp280.c"
#include "assets/lcd/lcd_serial.c"
//-----------------------------------------------------------------------------------
uint8_t str[20], numStr[10];
//-----------------------------------------------------------------------------------
void setup(void)
{
  lcd_init();
  bmp280_init(osrs_t_x1, osrs_p_x1, normal_mode); // Initialize BMP280 with 1x oversampling for both temperature and pressure in normal mode
}
//-----------------------------------------------------------------------------------
void loop(void) 
{ 
  dtostrf(bmp280_getPres(), 7, 2, numStr);   // 7 chars min total width, 2 after decimal point
  sprintf(str, "Pres:%shPa", numStr);
  lcd_string(0, 0, str);
  
  dtostrf(bmp280_getTemp(), 5, 1, numStr);   // 5 chars min total width, 1 after decimal point
  sprintf(str, "Temp:%s°C", numStr);
  lcd_string(1, 0, str);
  delay(100);
}
//-----------------------------------------------------------------------------------