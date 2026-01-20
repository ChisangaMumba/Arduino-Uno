#ifndef SPI_H
#define	SPI_H
//------------------------------------------------------------------------------
uint8_t SCLK  = 13; 
uint8_t SDOUT = 12;
uint8_t SDIN  = 11;
//------------------------------------------------------------------------------
void SPI_init(void)
{
  pinMode(SCLK, OUTPUT);
  pinMode(SDOUT, OUTPUT);
  pinMode(SDIN, INPUT);
}
//--------------------------TX: transmit _data-----------------------------------
void SPI_write(uint8_t send)
{	
	for(uint8_t tx = 0; tx < 8; tx++)
	{
		digitalWrite(SCLK, LOW);        //SCLK = 0;
    digitalWrite(SDOUT, ((send << tx) & 0x80) ? HIGH : LOW);  //MSB first
		digitalWrite(SCLK, HIGH);       //SCLK = 1;
	}
}
//--------------------------RX: recieve _data------------------------------------
uint8_t SPI_read(void)
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