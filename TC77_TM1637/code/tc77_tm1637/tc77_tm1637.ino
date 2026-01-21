//-----------------------------------------------------------------------------------
#include "assets/tc77/tc77.c"
#include "assets/tm1637/tm1637.c"
//-----------------------------------------------------------------------------------
uint8_t str[12];  
float tempr;
//-----------------------------------------------------------------------------------
void setup()
{
  tm1637_init(8);   // Initialize TM1637 with maximum brightness
  tc77_init(4);     // CS Pin = 4, Temperature mode (continuous conversion)
}
//-----------------------------------------------------------------------------------
void loop() 
{
  tempr = tc77_getTemp();
  
  dtostrf(tempr, 5, 1, str);        // 5 chars min total width, 1 after decimal point
  strcat(str, "°C");        
  
  tm1637_displayNumText(str);       // Display temperature on TM1637
  delay(300);  
}
//-----------------------------------------------------------------------------------