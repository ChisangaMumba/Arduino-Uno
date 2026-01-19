//-----------------------------------------------------------------------------------
#include "assets/ds18b20.c"
#include "assets/tm1637/tm1637.c"
//-----------------------------------------------------------------------------------
void setup()
{
  TM1637_init(7);
}
//-----------------------------------------------------------------------------------
uint8_t str[10], numStr[10];
unsigned int rawTemp = 0;
float tempr = 0;
//-----------------------------------------------------------------------------------
void loop() 
{
  if(ds18b20_read(&rawTemp))
  {
    tempr = ds18b20_toFloat(rawTemp);

    dtostrf(tempr, 5, 1, numStr);   // 5 chars min total width, 1 after decimal point
    sprintf(str, "%s°c", numStr);
    TM1637_displayNumText(str);
  }
  else
      {
        TM1637_displayNumText("Error"); 
      }
}
//-----------------------------------------------------------------------------------