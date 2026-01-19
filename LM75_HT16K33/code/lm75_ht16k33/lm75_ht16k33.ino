//-----------------------------------------------------------------------------------
#include "assets/lm75/LM75.c"
#include "assets/ht16k33/ht16k33.c"
//-----------------------------------------------------------------------------------
void setup()
{
  ht16k33_init();
  LM75_init();
}
//-----------------------------------------------------------------------------------
uint8_t str[10], numStr[10];
void loop() 
{
  // float temp = -287.9;

  dtostrf(LM75_read(TEMPERATURE_ADDRESS), 7, 1, numStr);   // 7 chars min total width, 1 after decimal point
  sprintf(str, "%s°c", numStr);    
  
  ht16k33_displayText(str);
}
//-----------------------------------------------------------------------------------