#ifndef DS18B20_C
#define	DS18B20_C
//------------------------------------------------------------------------------
#include "ds18b20.h"
//------------------------------------------------------------------------------
void ds18b20_init(uint8_t highTemp, uint8_t lowTemp, uint8_t res)
{
  ds18b20_command(WRITE_SCRATCHPAD);

  ds18b20_write(highTemp); // high temperature threshold for thermostat
  ds18b20_write(lowTemp);  // low temperature threshold for thermostat
  ds18b20_write(res);      // ADC resolution setting
}
//------------------------------------------------------------------------------
uint8_t ds18b20_start(void)
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
void ds18b20_write(uint8_t data)
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
uint8_t ds18b20_read(void)
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
uint8_t ds18b20_command(uint8_t data)
{
  if(!ds18b20_start())
  {
    return 0;             // return 0 if error
  }

  ds18b20_write(SKIP_ROM);   
  ds18b20_write(data);  	

  return 1;
}
//------------------------------------------------------------------------------
uint8_t ds18b20_getData(uint8_t data[])
{
  if(!ds18b20_command(START_CONVERSION))
  {
    return 0;                      // return 0 if error
  }
  
  while(ds18b20_read() == 0);  // wait for conversion complete
  
  if(!ds18b20_command(READ_SCRATCHPAD))
  {
    return 0;
  }
  
  for(uint8_t i = 0; i < 9; i++)
  {
    data[i] = ds18b20_read();
  }
  
  return 1;                        // OK --> return 1
}
//------------------------------------------------------------------------------
uint8_t ds18b20_calcCRC(uint8_t data[], uint8_t size)
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
uint8_t ds18b20_isDataValid(uint8_t data[], uint8_t size)
{
	uint8_t isValid = 0;
	
	if(ds18b20_calcCRC(data, size) == data[8])        // data[8] == CRC value
	{
		isValid = 1;
	}
	
	return isValid;
}
//------------------------------------------------------------------------------
void ds18b20_setFields(ds18b20_t *sensor, uint8_t data[])
{
  if(sensor == NULL || data == NULL) 
  {
    return; // Return if sensor or data pointer is NULL
  }

  sensor->rawTemp = (data[1] << 8) + data[0]; // Combine high and low byte
  sensor->temperature = toFloat(sensor->rawTemp);
  sensor->tempHigh = data[2];                 // High temperature threshold
  sensor->tempLow = data[3];                  // Low temperature threshold);
  sensor->config = data[4];                   // Configuration byte
  sensor->resIndex = (data[4] &  0x60) >> 5;; // Initialize resolution index
  sensor->crc = data[8];                      // CRC value
}
//------------------------------------------------------------------------------
void ds18b20_convDelay(uint8_t resInd)
{
		switch(resInd) 
		{
			case(0): delay(94);  break;   // 9-bit  res 93.75ms conversion time
			case(1): delay(188); break;   // 10-bit res 187.5ms conversion time
			case(2): delay(375); break;   // 11-bit res 375ms conversion time
			case(3): delay(750); break;   // 12-bit res (Power-up default) 750ms conversion time
		}
}
//------------------------------------------------------------------------------
float toFloat(int16_t rawData)
{
  float tempr = rawData >> 4;     
  uint16_t count = rawData & FRAC_FLAG;          

  if(count) 
  {
    tempr += (count * 0.0625); // 2^(-4) = 0.0625 (result is in multiples of 0.0625 LSBit for 12-bit res ADC)
  }

  return tempr;
}
//------------------------------------------------------------------------------
#endif	/* DS18B20_C */