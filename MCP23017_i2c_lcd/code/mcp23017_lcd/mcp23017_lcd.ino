//----------------------------------------------------------------------------------
#include "assets/lm75/LM75.c"
#include "assets/Lcd/LCD_Serial.c"
//----------------------------------------------------------------------------------
void setup() 
{
  LCD_init();
  LM75_init();
}
//----------------------------------------------------------------------------------
char str[18], numStr[18];
void loop() 
{
  dtostrf(LM75_read(TEMPERATURE_ADDRESS), 5, 1, numStr);   // 5 chars min total width, 1 after decimal point
  sprintf(str, "Temp: %s°C", numStr);  

	LCD_string(0, 2, "MCP23017 Lcd");
	LCD_string(1, 0, str);
}
//----------------------------------------------------------------------------------