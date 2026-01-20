//-----------------------------------------------------------------------------------
#include "assets/mcp9800/mcp9800.c"
#include "assets/ht16k33/ht16k33.c"
//-----------------------------------------------------------------------------------
uint8_t str[12], addr = 0x90; // Temperature sensor device Address
float tempr;
//-----------------------------------------------------------------------------------
void setup()
{
  ht16k33_init();
  mcp9800_init(addr, RES11_BIT);
}
//-----------------------------------------------------------------------------------
void loop() 
{
  tempr = mcp9800_getTemperature(addr);

  dtostrf(tempr, 7, 3, str);   // 7 chars min total width, 3 after decimal point
  strcat(str, "°C");  
  ht16k33_displayText(str);

  delay(500);
}
//-----------------------------------------------------------------------------------