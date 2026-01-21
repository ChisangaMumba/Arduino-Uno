//-----------------------------------------------------------------------------------
#include "assets/ht16k33/ht16k33.c"
#include "assets/mcp9800/mcp9800.c"
//-----------------------------------------------------------------------------------
uint8_t str[12];                // Buffer for temperature string
float tempr = 0;
//-----------------------------------------------------------------------------------
void setup(void)
{
  ht16k33_init(15);             // Initialize HT16K33 with brightness level 15 
  mcp9800_init(RES11_BIT);
}
//-----------------------------------------------------------------------------------
void loop(void)
{      
  tempr = mcp9800_getTemp();
  dtostrf(tempr, 7, 3, str);    // 7 chars min total width, 3 after decimal point
  
  strcat(str, "°C");
  ht16k33_displayText(str);
}
//-----------------------------------------------------------------------------------