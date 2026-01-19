//------------------------------------------------------------------------------
#include "assets/tc72/tc72.c"
#include "assets/Segments/Segments.c"
//------------------------------------------------------------------------------
int16_t tempr;
int8_t numStr[10];
//------------------------------------------------------------------------------
void setup() 
{
  Segments_init();
  TC72_init();
}
//------------------------------------------------------------------------------
void loop() 
{  
  tempr = TC72_readTempr();

  dtostrf(calcTempr(tempr), 5, 1, numStr);   // 5 chars min total width, 1 after decimal point
 
  Segments_displayText(FIFO, numStr);
}
//------------------------------------------------------------------------------