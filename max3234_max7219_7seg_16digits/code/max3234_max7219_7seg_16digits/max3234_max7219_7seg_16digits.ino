//------------------------------------------------------------------------------
#include "assets/ds3234/ds3234.c"
#include "assets/max7219/max7219.c"
//------------------------------------------------------------------------------
char str[30];
uint8_t time[8];
time_t tm; 
//------------------------------------------------------------------------------
void setup(void) 
{
  max7219_init(2);    //Number of chips connected in daisy chain
  ds3234_init(time);  //Initialize DS3234 RTC with initial time
}
//------------------------------------------------------------------------------
void loop(void) 
{  
  ds3234_getDateTime(&tm, time);
  
  sprintf(str, "%02d.%02d.%02d  ", tm.hour, tm.minute, tm.second); // Format time as HH.MM.SS
  sprintf(str + strlen(str), "%02d.%02d.20%02d", tm.dayOfMonth, tm.month, tm.year); // Format date as DD.MM.YYYY
  
  max7219_displayText(str);
  delay(100);
}
//------------------------------------------------------------------------------