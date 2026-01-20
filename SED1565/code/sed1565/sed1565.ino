//----------------------------------------------------------------------------------
#include "assets/sed1565/sed1565.c"
#include "assets/lm75/lm75.c"
//----------------------------------------------------------------------------------
uint8_t str[34], numStr[12];
//----------------------------------------------------------------------------------
void setup() 
{
	SED1565_init();
	// SED1565_image(img);
	lm75_init(32, -5);  // Thermostat: High, Low

	SED1565_print(0, 45, "Nokia 711");
	SED1565_print(2, 0,  "Thermostat");
	SED1565_print(6, 0,  "Temperature");
}
//----------------------------------------------------------------------------------
void loop() 
{
	dtostrf(lm75_getTemp(TOS_REG), 5, 1, numStr);   // 5 chars min total width, 1 after decimal point
	sprintf(str, "High: %s°C", numStr);
	SED1565_print(3, 0, str);
  
	dtostrf(lm75_getTemp(THYST_REG), 5, 1, numStr); 
	sprintf(str, "Low:  %s°C", numStr);
	SED1565_print(4, 0, str);
  
	dtostrf(lm75_getTemp(TEMP_REG), 5, 1, numStr); 
	sprintf(str, "Value: %s°C", numStr);
	SED1565_print(7, 0, str);
}
//----------------------------------------------------------------------------------