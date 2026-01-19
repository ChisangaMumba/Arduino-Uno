//------------------------------------------------------------------------------
#include "assets/tc72.c"
#include "assets/nokia/nokia_glcd.c"
//------------------------------------------------------------------------------
signed int tempr;
char str[18], numStr[18];
//------------------------------------------------------------------------------
void setup() 
{
  LCD_init();
  TC72_init();
  //LCD_image(img);
  LCD_string(0, 2, "Nokia 3310");
  LCD_string(2, 3, "TC72 SPI");
}
//------------------------------------------------------------------------------
void loop() 
{  
  tempr = TC72_readTempr();

  dtostrf(calcTempr(tempr), 6, 2, numStr);   // 6 chars min total width, 1 after decimal point
  sprintf(str, "Temp: %s°C", numStr, '%');  

  LCD_string(5, 0, str); 
}
//------------------------------------------------------------------------------