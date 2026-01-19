//------------------------------------------------------------------------------
#include "assets/tc72/tc72.c"
#include "assets/Lcd/LCD_Serial.c"
//------------------------------------------------------------------------------
signed int tempr;
char str[18], numStr[18];
//------------------------------------------------------------------------------
void setup() 
{
  LCD_init();
  TC72_init();

  LCD_string(0, 0, "MCP23S17 SPI Lcd");
}
//------------------------------------------------------------------------------
void loop() 
{  
  tempr = TC72_readTempr();

  dtostrf(calcTempr(tempr), 6, 2, numStr);   // 6 chars min total width, 2 after decimal point
  sprintf(str, "Temp: %s°C", numStr);  

  LCD_string(1, 0, str); 
}
//------------------------------------------------------------------------------