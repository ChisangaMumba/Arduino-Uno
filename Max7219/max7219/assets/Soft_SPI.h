#ifndef SPI_H
#define	SPI_H
//------------------------------------------------------------------------------
uint8_t SCLK = 11; 
uint8_t SDOUT = 10;
uint8_t SDIN = 9;
uint8_t CS = 8;
//------------------------------------------------------------------------------
void SPI_init(void)
{
  pinMode(SCLK, OUTPUT);
  pinMode(SDOUT, OUTPUT);
  pinMode(SDIN, INPUT);
  pinMode(CS, OUTPUT);
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
char SPI_read(void)
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