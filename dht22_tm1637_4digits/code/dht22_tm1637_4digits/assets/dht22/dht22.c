#ifndef DHT22_C
#define	DHT22_C
//------------------------------------------------------------------------------
uint8_t DATA_PIN = 10; // Pin connected to DHT22 data pin
//------------------------------------------------------------------------------
void oneWire_start()			
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

	while(digitalRead(DATA_PIN) == 1);     // wait for DHT22 low pulse
	while(digitalRead(DATA_PIN) == 0);     // wait for DHT22 high pulse
	while(digitalRead(DATA_PIN) == 1);     // wait for DHT22 low pulse
	
	response = 1;
	
	return response;
}
//------------------------------------------------------------------------------
uint8_t oneWire_readByte()		
{
	uint8_t dataByte = 0;	
	
	for(uint8_t i = 0; i < 8; i++)
	{
		while(digitalRead(DATA_PIN) == 0);   // wait for DHT22 low pulse 
		
		delayMicroseconds(30);		
		if(digitalRead(DATA_PIN) == 1)       // If high pulse is greater than 30ms
		{
			dataByte += (0x01 << (7 - i));     // set bit (7 - i)
		}
		
		while(digitalRead(DATA_PIN) == 1);   // wait for DHT22 high pulse
	}
	
	return dataByte;
}
//------------------------------------------------------------------------------
uint8_t dht22_calcChecksum(uint8_t sensorData[])
{
	uint8_t checksum = 0;
	
	for(uint8_t i = 0; i < 4; i++)
	{
		checksum += sensorData[i];
	}
	
	return checksum;
}
//------------------------------------------------------------------------------
uint8_t dht22_isChecksumInvalid(uint8_t sensorData[])
{
	uint8_t isInvalid = 0;
	
	if(dht22_calcChecksum(sensorData) != sensorData[4]) // sensorData[4] == checksum value
	{
		isInvalid = 1;
	}
	
	return isInvalid;
}
//------------------------------------------------------------------------------
int16_t dht22_getTemperature(uint8_t sensorData[])
{
	int16_t tempr = (sensorData[2] << 8) + sensorData[3];
		
	return tempr;
}
//------------------------------------------------------------------------------
int16_t dht22_getHumidity(uint8_t sensorData[])
{
	int16_t humidity = (sensorData[0] << 8) + sensorData[1];
		
	return humidity;
}
//------------------------------------------------------------------------------
void dht22_getSensorData(uint8_t sensorData[])
{
	for(uint8_t i = 0; i < 5; i++)
	{
		sensorData[i] = oneWire_readByte();
	}
}
//------------------------------------------------------------------------------
float calcTempr(int16_t rawData)
{
	float tempr = rawData;  
   	
	if(rawData & 0x8000) //if 16th bit is a 1, num is negative (sign magnitude signed number)
	{
	  tempr = -1 * (rawData & 0x7fff);
	}

	return tempr/10;
}
//------------------------------------------------------------------------------
#endif