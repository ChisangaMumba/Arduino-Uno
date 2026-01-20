#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#define ACK  0
#define NACK 1
//------------------------------------------------------------------------------
uint8_t SCLK = 12;
uint8_t SDAT = 11;
//------------------------------------------------------------------------------ 
void I2C_init()
{
  // Note I2C SDA is open drain, this means we need to use INPUT for an SDA high logic. I.e. we can't just write digitalWrite(pin, HIGH) for the SDA.
  pinMode(SCLK, OUTPUT);

  pinMode(SDAT, INPUT);       // SDAT = 1
  digitalWrite(SCLK, HIGH);   // SCLK = 1
}
//------------------------------------------------------------------------------ 
void I2C_start()
{
  pinMode(SDAT, OUTPUT);     // SDAT = 0
  digitalWrite(SCLK, LOW);   // SCLK = 0
}
//------------------------------------------------------------------------------ 
void I2C_restart()
{
  pinMode(SDAT, INPUT);       // SDAT = 1
  digitalWrite(SCLK, HIGH);   // SCLK = 1
  pinMode(SDAT, OUTPUT);      // SDAT = 0
  digitalWrite(SCLK, LOW);    // SCLK = 0
}
//------------------------------------------------------------------------------ 
void I2C_stop()
{
  digitalWrite(SCLK, LOW);    // SCLK = 0
  pinMode(SDAT, OUTPUT);      // SDAT = 0
  digitalWrite(SCLK, HIGH);   // SCLK = 1
  pinMode(SDAT, INPUT);       // SDAT = 1
}
//------------------------------------------------------------------------------ 
void I2C_ack(uint8_t ackn)
{
  pinMode(SDAT, (ackn == 1) ? INPUT : OUTPUT);   // SDAT = ackn; 
  digitalWrite(SCLK, HIGH);                      // SCLK = 1
  digitalWrite(SCLK, LOW);                       // SCLK = 0
  pinMode(SDAT, INPUT);                          // SDAT = 1
}
//------------------------------------------------------------------------------ 
uint8_t I2C_write(uint8_t data)
{	
  for(uint8_t tx = 0; tx < 8; tx++)
  {
    pinMode(SDAT, ((data << tx) & 0x80) ? INPUT : OUTPUT) ; //MSB first SDAT 1 or 0
    digitalWrite(SCLK, HIGH);   // SCLK = 1
    digitalWrite(SCLK, LOW);    // SCLK = 0 //Toggle SCK pin So that slave can latch data bit                   
  }
	
  I2C_ack(ACK);
	
  return SDAT;
}
//------------------------------------------------------------------------------ 
uint8_t I2C_read(uint8_t ackState)
{
	uint8_t data = 0;

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