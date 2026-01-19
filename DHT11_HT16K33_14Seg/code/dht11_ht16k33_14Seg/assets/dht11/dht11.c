#ifndef DHT11_C
#define	DHT11_C
//------------------------------------------------------------------------------
uint8_t DATA_PIN = 9;
//------------------------------------------------------------------------------
void oneWire_start()			// Microcontroller send request
{
	pinMode(DATA_PIN, OUTPUT);

	digitalWrite(DATA_PIN, LOW);	
	delay(20);	                       // delayMiliseconds
	digitalWrite(DATA_PIN, HIGH);	
}
//------------------------------------------------------------------------------
uint8_t oneWire_getResponse()			
{
	uint8_t response = 0;
		
	pinMode(DATA_PIN, INPUT);

	while(digitalRead(DATA_PIN) == 1);     // wait for DHT11 low pulse
	while(digitalRead(DATA_PIN) == 0);     // wait for DHT11 high pulse
	while(digitalRead(DATA_PIN) == 1);     // wait for DHT11 low pulse
		
	response = 1;
		
	return response;
}
//------------------------------------------------------------------------------
uint8_t oneWire_readByte()		
{
	uint8_t i, dataByte = 0;	
	
	for(i = 0; i < 8; i++)
	{
		while(digitalRead(DATA_PIN) == 0);   // wait for DHT11 low pulse 
		
		delayMicroseconds(30);		
		if(digitalRead(DATA_PIN) == 1)       // If high pulse is greater than 30ms
		{
			dataByte += (0x01 << (7 - i));     // set bit (7 - i)
		}
		
		while(digitalRead(DATA_PIN) == 1);   // wait for DHT11 high pulse
	}
	
	return dataByte;
}
//------------------------------------------------------------------------------
uint8_t dht11_calcChecksum(uint8_t sensorData[])
{
	uint8_t i, checksum = 0;
	
	for(i = 0; i < 4; i++)
	{
		checksum += sensorData[i];
	}
	
	return checksum;
}
//------------------------------------------------------------------------------
uint8_t dht11_isChecksumInvalid(uint8_t sensorData[])
{
	uint8_t isInvalid = 0;
	
	if(dht11_calcChecksum(sensorData) != sensorData[4]) // sensorData[4] == checksum value
	{
		isInvalid = 1;
	}
	
	return isInvalid;
}
//------------------------------------------------------------------------------
int16_t dht11_getTemperature(uint8_t sensorData[])
{
  int16_t tempr = (sensorData[3] << 8) + sensorData[2];
    
  return tempr;
}
//------------------------------------------------------------------------------
int16_t dht11_getHumidity(uint8_t sensorData[])
{
	int16_t humidity = (sensorData[1] << 8) + sensorData[0];
    
  return humidity;
}
//------------------------------------------------------------------------------
void dht11_getSensorData(uint8_t sensorData[])
{
	for(uint8_t i = 0; i < 5; i++)
	{
		sensorData[i] = oneWire_readByte();
	}
}
//------------------------------------------------------------------------------
#endif