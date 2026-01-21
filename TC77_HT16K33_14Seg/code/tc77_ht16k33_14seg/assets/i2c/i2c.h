#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#define ACK  0
#define NACK 1
//------------------------------------------------------------------------------
uint8_t SCL_ = 13;
uint8_t SDA_ = 12;
//------------------------------------------------------------------------------ 
void I2C_init()
{
  // Note I2C SDA_ is open drain, this means we need to use INPUT for an SDA_ high logic. I.e. we can't just write digitalWrite(pin, HIGH) for the SDA_.
  pinMode(SCL_, OUTPUT);

  pinMode(SDA_, INPUT);       // SDA_ = 1
  digitalWrite(SCL_, HIGH);   // SCL_ = 1
}
//------------------------------------------------------------------------------ 
void I2C_start()
{
  pinMode(SDA_, OUTPUT);     // SDA_ = 0
  digitalWrite(SCL_, LOW);   // SCL_ = 0
}
//------------------------------------------------------------------------------ 
void I2C_restart()
{
  pinMode(SDA_, INPUT);       // SDA_ = 1
  digitalWrite(SCL_, HIGH);   // SCL_ = 1
  pinMode(SDA_, OUTPUT);      // SDA_ = 0
  digitalWrite(SCL_, LOW);    // SCL_ = 0
}
//------------------------------------------------------------------------------ 
void I2C_stop()
{
  digitalWrite(SCL_, LOW);    // SCL_ = 0
  pinMode(SDA_, OUTPUT);      // SDA_ = 0
  digitalWrite(SCL_, HIGH);   // SCL_ = 1
  pinMode(SDA_, INPUT);       // SDA_ = 1
}
//------------------------------------------------------------------------------ 
void I2C_ack(uint8_t ackn)
{
  pinMode(SDA_, (ackn == 1) ? INPUT : OUTPUT);   // SDA_ = ackn; 
  digitalWrite(SCL_, HIGH);                      // SCL_ = 1
  digitalWrite(SCL_, LOW);                       // SCL_ = 0
  pinMode(SDA_, INPUT);                          // SDA_ = 1
}
//------------------------------------------------------------------------------ 
uint8_t I2C_write(uint8_t data)
{	
  for(uint8_t tx = 0; tx < 8; tx++)
  {
    pinMode(SDA_, ((data << tx) & 0x80) ? INPUT : OUTPUT) ; //MSB first SDA_ 1 or 0
    digitalWrite(SCL_, HIGH);   // SCL_ = 1
    digitalWrite(SCL_, LOW);    // SCL_ = 0 //Toggle SCK pin So that slave can latch data bit                   
  }
	
  I2C_ack(ACK);
	
  return SDA_;
}
//------------------------------------------------------------------------------ 
uint8_t I2C_read(uint8_t ackState)
{
	uint8_t data = 0;

	for(uint8_t rx = 0; rx < 8; rx++) 
	{
		digitalWrite(SCL_, HIGH);   // SCL_ = 1
    
    data += digitalRead(SDA_) << (7-rx);  //MSB first
    
		digitalWrite(SCL_, LOW);    // SCL_ = 0
	}
	
	I2C_ack(ackState);
	
	return data;
}
//------------------------------------------------------------------------------
#endif