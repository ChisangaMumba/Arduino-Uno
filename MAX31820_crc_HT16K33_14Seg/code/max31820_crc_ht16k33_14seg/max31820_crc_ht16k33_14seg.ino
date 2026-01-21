//-----------------------------------------------------------------------------------
#include "assets/max31820/max31820.c"
#include "assets/ht16k33/ht16k33.c"
//-----------------------------------------------------------------------------------
uint8_t str[12], sensorData[9];
float tempr = 0;
//-----------------------------------------------------------------------------------
void setup()
{
  ht16k33_init(15);  // Initialize HT16K33 with brightness level 15 
  max31820_init(34, 22, RES_11_BIT);  //High, Low, Resolution
}
//-----------------------------------------------------------------------------------
void loop() 
{
  uint8_t ok = max31820_getData(sensorData);

  if(ok == 1 && max31820_isDataValid(sensorData) == 1)
  {       
    tempr = max31820_getTempr(sensorData);
    dtostrf(tempr, 7, 3, str);           // 7 chars min total width, 3 after decimal point
    
    strcat(str, "°C");
    ht16k33_displayText(str);
  }
  else
      {
        ht16k33_displayText("Error   "); 
      }
}
//-----------------------------------------------------------------------------------