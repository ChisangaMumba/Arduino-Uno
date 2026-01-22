//-----------------------------------------------------------------------------------
#include "assets/ds3232/ds3232.c"
#include "assets/tm1637/tm1637.c"
//-----------------------------------------------------------------------------------
uint8_t time[8] = {55, 0, 12, 1, 1, 1, 25}; // Initial time data in BCD format
// 55 seconds, 00 minutes, 12 hours, 1st day of the week (Sunday), 1st day of the month, January, year 2025
// This will be used to initialize the DS3232 RTC
time_t tm;
//-----------------------------------------------------------------------------------
void setup(void)
{
  tm1637_init(7);   // Initialize tm1637 with brightness level 7 
  ds3232_init(time); // Initialize DS3232 with the initial time array. Uncomment the line that sets the initial date and time in the function that initializes the DS3232
}
//-----------------------------------------------------------------------------------
void loop(void) 
{  
  ds3232_getDateTime(&tm, time); // Get the current time from the DS3232

  // tm1637_displayText(tm.date); // Display formatted date
  tm1637_displayText(tm.time); // Display formatted time

  delay(500);
}
//-----------------------------------------------------------------------------------