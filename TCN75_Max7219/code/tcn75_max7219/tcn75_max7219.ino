//-----------------------------------------------------------------------------------
#include "assets/tcn75/tcn75.c"
#include "assets/max7219/max7219.c"
//-----------------------------------------------------------------------------------
uint8_t str[12];  
float tempr;
//-----------------------------------------------------------------------------------
void setup()
{
  max7219_init(SCAN_ALL_DIGITS);
  tcn75_init(32, 20, RES_10_BIT);  //High, Low, Resolution
}
//-----------------------------------------------------------------------------------
void loop() 
{
  tempr = tcn75_getTemp(TEMP_REG);
  
  dtostrf(tempr, 7, 2, str);        // 7 chars min total width, 2 after decimal point
  strcat(str, "°C");        
  
  max7219_displayText(str);

  delay(250);  // Update every 250 ms
  // Alternatively, you can use a longer delay for less frequent updates  
}
//-----------------------------------------------------------------------------------