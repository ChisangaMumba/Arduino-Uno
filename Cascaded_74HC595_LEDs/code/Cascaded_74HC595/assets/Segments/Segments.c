#ifndef SEGMENT_FUNCTIONS_H
#define	SEGMENT_FUNCTIONS_H
//------------------------------------------------------------------------------
#include "../SPI/Soft_SPI.h"
#include "../74HC595/74HC595.c"
//------------------------------------------------------------------------------
void Segments_init();
void Segments_displayNum(uint8_t sendMode, int16_t number);
void Segments_displayText(uint8_t sendMode, uint8_t text[]);
//------------------------------------------------------------------------------
void Segments_init()
{
  SPI_init();
  ShiftReg_init();
  Segments_displayText(FIFO, "    ");
}
//------------------------------------------------------------------------------
void Segments_displayNum(uint8_t sendMode, int16_t number)
{     
  uint8_t strNum[10];
  sprintf(strNum, "%4i", number);

	Segments_displayText(sendMode, strNum);
}
//------------------------------------------------------------------------------
void Segments_displayText(uint8_t sendMode, uint8_t text[])
{
	switch(sendMode)
  {
    case 0: ShiftReg_FIFOSend(text); break;  
    case 1: ShiftReg_LIFOSend(text); break;
  }
}
//------------------------------------------------------------------------------
#endif