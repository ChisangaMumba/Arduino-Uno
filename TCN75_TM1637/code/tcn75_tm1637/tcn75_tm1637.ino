//-----------------------------------------------------------------------------------
#include "assets/tcn75/tcn75.c"
#include "assets/tm1637/tm1637.c"
//-----------------------------------------------------------------------------------
uint8_t str[12];  
float tempr;
//-----------------------------------------------------------------------------------
void setup()
{
  tm1637_init(8);  // Initialize TM1637 with maximum brightness
  tcn75_init(32, 20, RES_09_BIT);  //High, Low, Resolution
}
//-----------------------------------------------------------------------------------
void loop() 
{
  tempr = tcn75_getTemp(TEMP_REG);
  
  dtostrf(tempr, 5, 1, str);        // 5 chars min total width, 1 after decimal point
  strcat(str, "°C");        
  
  tm1637_displayNumText(str);       // Display temperature on TM1637
  delay(250);  // Update every 250 ms
}
//-----------------------------------------------------------------------------------