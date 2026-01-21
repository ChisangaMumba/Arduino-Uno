//------------------------------------------------------------------------------
#include "assets/tc77/tc77.c"
#include "assets/max7219/max7219.c"
//------------------------------------------------------------------------------
float tempr = 0.0f; 
char numStr[15]; // Buffer for temperature string, adjust size as needed
//------------------------------------------------------------------------------
void setup(void) 
{
  max7219_init(5);    //Number of chips
  tc77_init();
}
//------------------------------------------------------------------------------
void loop(void) 
{  
  tempr = tc77_getTemp();
  dtostrf(tempr, 5, 1, numStr); // 5 chars min total width, 1 after decimal point  

  strcat(numStr, "°C"); // Append degree symbol and unit
  max7219_displayText(numStr); 
}
//------------------------------------------------------------------------------