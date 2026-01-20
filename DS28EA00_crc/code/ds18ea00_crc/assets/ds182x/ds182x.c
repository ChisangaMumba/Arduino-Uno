#ifndef DS182x_C
#define	DS182x_C
//------------------------------------------------------------------------------
#include "ds182x.h"
//------------------------------------------------------------------------------
void ds182x_init(uint8_t highTemp, uint8_t lowTemp, uint8_t res)
{
  ds182x_command(WRITE_SCRATCHPAD);

  ds182x_writeByte(highTemp);
  ds182x_writeByte(lowTemp);
  ds182x_writeByte(res);
}
//------------------------------------------------------------------------------
uint8_t ds182x_start()
{	
  digitalWrite(DQ_PIN, LOW);    //DQ_PIN = 0  send reset pulse to the DS182x sensor       
  
  pinMode(DQ_PIN, OUTPUT);      // configure DQ_PIN pin as outpu
  delayMicroseconds(500);    

  pinMode(DQ_PIN, INPUT);       //DQ_PIN = 1  configure DQ_PIN pin as input 
  delayMicroseconds(100);       // wait 100 us to read the DS182x sensor response
  
  if(!digitalRead(DQ_PIN))
  {
    delayMicroseconds(400);      // wait 400 us
    return 1;                    // DS182x sensor is present
  }

	return 0;                      // connection error
}
//------------------------------------------------------------------------------ 
void ds182x_writeByte(uint8_t data)
{
  for(uint8_t i = 0; i < 8; i++)
  {
    pinMode(DQ_PIN, OUTPUT);                    // CLK = 0

    digitalWrite(DQ_PIN, ((data >> i) & 0x01) ? HIGH : LOW);  // DATA = 1 0r DATA = 0

    delayMicroseconds(50);
    pinMode(DQ_PIN, INPUT);                     // CLK = 1
  }
}
//------------------------------------------------------------------------------ 
uint8_t ds182x_readByte()
{
  uint8_t data = 0;
     
  for(uint8_t i = 0; i < 8; i++)
  {
    pinMode(DQ_PIN, OUTPUT);          // CLK = 0
    pinMode(DQ_PIN, INPUT);           // CLK = 1   

    data += digitalRead(DQ_PIN) << i; // data = DATA
    
    delayMicroseconds(50);      
  }
  
  return data;
}
//------------------------------------------------------------------------------
uint8_t ds182x_command(uint8_t data)
{
  if(!ds182x_start())
  {
    return 0;             // return 0 if error
  }

  ds182x_writeByte(SKIP_ROM);   
  ds182x_writeByte(data);  	

  return 1;
}
//------------------------------------------------------------------------------
uint8_t ds182x_getData(uint8_t data[])
{
  if(!ds182x_command(START_CONVERSION))
  {
    return 0;                      // return 0 if error
  }
  
  while(ds182x_readByte() == 0);  // wait for conversion complete
  
  if(!ds182x_command(READ_SCRATCHPAD))
  {
    return 0;
  }
  
  for(uint8_t i = 0; i < 9; i++)
  {
    data[i] = ds182x_readByte();
  }
  
  return 1;                        // OK --> return 1
}
//------------------------------------------------------------------------------
float ds182x_getTempr(uint8_t data[])
{    
  int16_t tempr  = (data[1] <<    8) +  data[0];
  uint8_t resInd = (data[4] &  0x60) >> 5;        //get resolution 
  
  return toFloat(tempr, resInd);
}
//------------------------------------------------------------------------------
int8_t ds182x_getTH(uint8_t data[])
{
  return data[2];
}
//------------------------------------------------------------------------------
int8_t ds182x_getTL(uint8_t data[])
{
  return data[3];
}
//------------------------------------------------------------------------------
uint8_t ds182x_getConfig(uint8_t data[])
{
  return data[4]; 
}
//------------------------------------------------------------------------------
uint8_t ds182x_calcCRC(uint8_t data[], uint8_t size)
{
  uint8_t i, crc = 0;

  while(size--)
  {
    crc ^= *data++;

    for(i = 0; i < 8; i++) 
    {
      crc = (crc & 0x01) ? (crc >> 1) ^ 0x8C : (crc >> 1);  //0x8C (see datasheet) x^8 + x^4 + x^3 + 1 => 0b 1000 1100
    }
  }
  
  return crc; 
}
//------------------------------------------------------------------------------
uint8_t ds182x_isDataValid(uint8_t data[], uint8_t size)
{
	uint8_t isValid = 0;
	
	if(ds182x_calcCRC(data, size) == data[8])        // data[8] == CRC value
	{
		isValid = 1;
	}
	
	return isValid;
}
//------------------------------------------------------------------------------
float toFloat(signed int tempr, uint8_t resInd)
{
  float result = (float) (tempr >> 4);     
  uint16_t count = tempr & FRAC_FLAG;          

  if(count) 
  {
    result += ((count >> (3-resInd)) * resValues[resInd]);
  }

  return result;
}
//------------------------------------------------------------------------------
#endif	/* DS182x_C */