#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#define ACK  0
#define NACK 1
//------------------------------------------------------------------------------
uint8_t SCLK = 9;
uint8_t SDAT = 8;
//------------------------------------------------------------------------------ 
void I2C_init()
{
  pinMode(SDAT, OUTPUT);
  pinMode(SCLK, OUTPUT);

  digitalWrite(SDAT, HIGH);   // SDAT = 1
  digitalWrite(SCLK, HIGH);   // SCLK = 1
}
//------------------------------------------------------------------------------ 
void I2C_start()
{
  digitalWrite(SDAT, LOW);   // SDAT = 0
  digitalWrite(SCLK, LOW);   // SCLK = 0
}
//------------------------------------------------------------------------------ 
void I2C_restart()
{
  digitalWrite(SDAT, HIGH);   // SDAT = 1
  digitalWrite(SCLK, HIGH);   // SCLK = 1
  digitalWrite(SDAT, LOW);    // SDAT = 0
  digitalWrite(SCLK, LOW);    // SCLK = 0
}
//------------------------------------------------------------------------------ 
void I2C_stop()
{
  digitalWrite(SCLK, LOW);    // SCLK = 0
  digitalWrite(SDAT, LOW);    // SDAT = 0
  digitalWrite(SCLK, HIGH);   // SCLK = 1
  digitalWrite(SDAT, HIGH);   // SDAT = 1
}
//------------------------------------------------------------------------------ 
void I2C_ack(uint8_t ackn)
{
  digitalWrite(SDAT, ackn);   // SDAT = ackn;
  digitalWrite(SCLK, HIGH);   // SCLK = 1
  digitalWrite(SCLK, LOW);    // SCLK = 0
  digitalWrite(SDAT, HIGH);   // SDAT = 1
}
//------------------------------------------------------------------------------ 
uint8_t I2C_write(uint8_t data)
{	
  for(uint8_t tx = 0; tx < 8; tx++)
  {
    digitalWrite(SDAT, ((data << tx) & 0x80) ? HIGH : LOW) ; //MSB first
    digitalWrite(SCLK, HIGH);   // SCLK = 1
    digitalWrite(SCLK, LOW);    // SCLK = 0 //Toggle SCK pin So that slave can latch data bit                   
  }
	
  I2C_ack(ACK);
	
  return SDAT;
}
//------------------------------------------------------------------------------ 
uint8_t I2C_read(uint8_t ackState)
{
	uint8_t data = 0, bit;
	
	for(uint8_t rx = 0; rx < 8; rx++) 
	{
		digitalWrite(SCLK, HIGH);   // SCLK = 1

		data += digitalRead(SDAT) << (7-rx);  //MSB first

		digitalWrite(SCLK, LOW);    // SCLK = 0
	}
	
	I2C_ack(ackState);
	
	return data;
}
//------------------------------------------------------------------------------
#endif