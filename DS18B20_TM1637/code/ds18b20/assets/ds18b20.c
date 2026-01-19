#ifndef DS18B20_H
#define	DS18B20_H
//------------------------------------------------------------------------------
#define FRAC_FLAG           0x000F
#define SKIP_ROM            0xCC
#define START_CONVERSION    0x44
#define READ_TEMPERATURE    0xBE
//------------------------------------------------------------------------------
uint8_t DQ_PIN = 3;
//------------------------------------------------------------------------------
uint8_t ds18b20_start()
{	
  digitalWrite(DQ_PIN, LOW);    //DQ_PIN = 0  send reset pulse to the DS18B20 sensor       
  
  pinMode(DQ_PIN, OUTPUT);      // configure DQ_PIN pin as outpu
  delayMicroseconds(500);    

  pinMode(DQ_PIN, INPUT);       //DQ_PIN = 1  configure DQ_PIN pin as input 
  delayMicroseconds(100);       // wait 100 us to read the DS18B20 sensor response
  
  if(!digitalRead(DQ_PIN))
  {
    delayMicroseconds(400);      // wait 400 us
    return 1;                    // DS18B20 sensor is present
  }

	return 0;                      // connection error
}
//------------------------------------------------------------------------------ 
void ds18b20_writeBit(uint8_t data)
{
  digitalWrite(DQ_PIN, LOW);
  pinMode(DQ_PIN, OUTPUT);                    // configure DQ_PIN pin as output
  delayMicroseconds(2);
  
  digitalWrite(DQ_PIN, (data) ? HIGH : LOW);  //DQ_PIN = 1 0r DQ_PIN = 
  delayMicroseconds(80);
  
  pinMode(DQ_PIN, INPUT);                     // configure DQ_PIN pin as input
  delayMicroseconds(2);
}
//------------------------------------------------------------------------------ 
void ds18b20_writeByte(uint8_t data)
{
  for(uint8_t i = 0; i < 8; i++)
  {
    ds18b20_writeBit((data >> i) & 0x01);  //LSB First
  }
}
//------------------------------------------------------------------------------ 
uint8_t ds18b20_readBit()
{
  uint8_t data = 0;
  
  digitalWrite(DQ_PIN, LOW);    //DQ_PIN = 0
  pinMode(DQ_PIN, OUTPUT);      //DQ_PIN_Dir = 0. configure DQ_PIN pin as output
  delayMicroseconds(2);
 
  pinMode(DQ_PIN, INPUT);       //DQ_PIN_Dir = 1. configure DQ_PIN pin as input
  delayMicroseconds(5);
 
  data = digitalRead(DQ_PIN);   //data = DQ_PIN. read and store DS18B20 state
  delayMicroseconds(100);      

  return data;
}
//------------------------------------------------------------------------------ 
int8_t ds18b20_readByte()
{
  int8_t data = 0;
     
  for(uint8_t i = 0; i < 8; i++)
  {
    data += ds18b20_readBit() << i;
  }
  
  return data;
}
//------------------------------------------------------------------------------
uint8_t ds18b20_command(uint8_t data)
{
  if(!ds18b20_start())
  {
    return 0;             // return 0 if error
  }
  ds18b20_writeByte(SKIP_ROM);   
  ds18b20_writeByte(data);  	

  return 1;
}
//------------------------------------------------------------------------------
uint8_t ds18b20_read(signed int *rawTempr)
{
  uint8_t temp[2];

  if(!ds18b20_command(START_CONVERSION))
  {
    return 0;                      // return 0 if error
  }
  
  while(ds18b20_readByte() == 0);  // wait for conversion complete
  
  if(!ds18b20_command(READ_TEMPERATURE))
  {
    return 0;
  }
  
  temp[0] = ds18b20_readByte();
  temp[1] = ds18b20_readByte();

  *rawTempr = (temp[1] << 8) + temp[0];
  
  return 1;                        // OK --> return 1
}
//------------------------------------------------------------------------------
float ds18b20_toFloat(signed int tempr)
{
  float result = (float) (tempr >> 4);     
  uint16_t count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
    result += (count * 0.0625);
  }
  
  return result;
}
//------------------------------------------------------------------------------
#endif	/* DS18B20_H */