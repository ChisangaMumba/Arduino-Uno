//-----------------------------------------------------------------------------------
#include "assets/LM75/LM75.h"
#include "assets/lcd/LCD_Serial.h"
//-----------------------------------------------------------------------------------
void setup()
{
  LCD_init(0x4E);
  LM75_init();

  LCD_string(0, 5, "PCF8574");
}
//-----------------------------------------------------------------------------------
float tempr;
uint8_t str[10], numStr[10];
void loop() 
{
  tempr = LM75_read(TEMPERATURE_ADDRESS);

  dtostrf(tempr, 7, 1, numStr);   // 7 chars min total width, 1 after decimal point
  sprintf(str, "Tempr: %s°C", numStr);    
  
  LCD_string(1, 0, str);
}
//-----------------------------------------------------------------------------------