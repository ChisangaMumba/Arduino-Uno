//-----------------------------------------------------------------------------------
#include "assets/mcp9800/mcp9800.c"
#include "assets/lcd/lcd_serial.c"
//-----------------------------------------------------------------------------------
float tempr;
uint8_t str[20], numStr[10];
int8_t tempHL[2];
//-----------------------------------------------------------------------------------
void setup()
{
  lcd_init();
  mcp9800_init(25, 11, RES11_BIT);  // Thermostat: High, Low, Resolution
  
  tempHL[1] = mcp9800_getTemp(TSET_REG);   // High thermostat value
  tempHL[0] = mcp9800_getTemp(THYST_REG);  // Low thermostat value

  sprintf(str, "H:%i, L:%i", tempHL[1], tempHL[0]); 
  lcd_string(1, 0, str);
}
//-----------------------------------------------------------------------------------
void loop() 
{ 
  tempr = mcp9800_getTemp();

  dtostrf(tempr, 7, 3, numStr);   // 7 chars min total width, 3 after decimal point
  
  sprintf(str, "Temp: %s°C", numStr);
  lcd_string(0, 0, str);
}
//-----------------------------------------------------------------------------------