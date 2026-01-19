//-----------------------------------------------------------------------------------
#include "assets/tm1638.c"
bool tempMode = 0;
//-----------------------------------------------------------------------------------
float getTemperature()
{
  float tempr = -28.93;
    
  return (tempMode == 0) ? tempr : (tempr * 9/5) + 32; // C or F
}
//-----------------------------------------------------------------------------------
void changeMode(uint8_t buttons)
{
  if(buttons == 0x80) 
    tempMode = !tempMode;
}
//-----------------------------------------------------------------------------------
void setup()
{
  pinMode(CLK, OUTPUT); 
  pinMode(DIO, OUTPUT);
  pinMode(STB, OUTPUT); 

  TM1638_init(7);
}
//-----------------------------------------------------------------------------------
char str[10], numStr[10];
void loop() 
{
  uint8_t buttons = TM1638_readButtons();
  ledFeedback(buttons);
  changeMode(buttons);

  dtostrf(getTemperature(), 7, 2, numStr);   // 7 chars min total width, 1 after decimal point
  sprintf(str, "%s°%c", numStr, (tempMode == 0) ? 'C' : 'F');
  TM1638_writeDisplay(str);
}
//-----------------------------------------------------------------------------------