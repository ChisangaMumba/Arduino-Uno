//-----------------------------------------------------------------------------------
#include "assets/bmp180/bmp180.c"
#include "assets/lcd/lcd_serial.c"
//-----------------------------------------------------------------------------------
float press, temp;
uint8_t str[20], numStr[10];
//-----------------------------------------------------------------------------------
void setup(void)
{
  lcd_init();
  bmp180_init();
}
//-----------------------------------------------------------------------------------
void loop(void) 
{ 
  press = bmp180_getPressure(OSS_value);
  temp = bmp180_getTemp();

  dtostrf(press, 6, 2, numStr);   // 6 chars min total width, 2 after decimal point
  sprintf(str, "Pres:%shPa", numStr);
  lcd_string(0, 0, str);

  dtostrf(temp, 5, 1, numStr);   // 5 chars min total width, 1 after decimal point
  sprintf(str, "Temp:%s°C", numStr);
  lcd_string(1, 0, str);
}
//-----------------------------------------------------------------------------------