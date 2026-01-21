#ifndef SPI_C
#define	SPI_C
//------------------------------------------------------------------------------
#include "soft_spi.h"  // Include the pin definitions for SCLK, SDOUT, and SDIN
//------------------------------------------------------------------------------
void spi_init(void)
{
  // Set the pin modes for SPI communication
  pinMode(SCLK, OUTPUT);
  pinMode(SDOUT, OUTPUT);
  pinMode(SDIN, INPUT);
}
//--------------------------TX: transmit _data-----------------------------------
void spi_write(uint8_t send)
{	
	for(uint8_t tx = 0; tx < 8; tx++)
	{
		digitalWrite(SCLK, LOW);        //SCLK = 0;
    digitalWrite(SDOUT, ((send << tx) & 0x80) ? HIGH : LOW);  //MSB first
		digitalWrite(SCLK, HIGH);       //SCLK = 1;
	}
}
//--------------------------RX: recieve _data------------------------------------
char spi_read(void)
{
  uint8_t data = 0;
  
  for(uint8_t Rx = 0 ; Rx < 8 ; Rx++)
  {
    digitalWrite(SCLK, LOW);        //SCLK = 0;
    data += digitalRead(SDIN) << (7-Rx);     //MSB first.
		digitalWrite(SCLK, HIGH);       //SCLK = 1;
  }

  return data;
}
//------------------------------------------------------------------------------
#endif