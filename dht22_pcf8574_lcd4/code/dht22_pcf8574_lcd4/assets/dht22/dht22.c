#ifndef DHT22_C
#define	DHT22_C
//------------------------------------------------------------------------------
#include "dht22.h"
//------------------------------------------------------------------------------
void oneWire_start(void)			
{
	pinMode(DATA_PIN, OUTPUT);

	digitalWrite(DATA_PIN, LOW);	
	delay(20);	                       // delayMiliseconds
	digitalWrite(DATA_PIN, HIGH);	
}
//------------------------------------------------------------------------------
uint8_t oneWire_getResponse(void)			
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
uint8_t oneWire_read8(void)		
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
uint8_t dht22_isDataValid(uint8_t sensorData[])
{
	uint8_t isValid = 0;
	
	if(dht22_calcChecksum(sensorData) == sensorData[4]) // sensorData[4] == checksum value
	{
		isValid = 1;
	}
	
	return isValid;
}
//------------------------------------------------------------------------------
uint8_t dht22_getSensorData(uint8_t sensorData[])
{
	oneWire_start();

	// Start communication with DHT22 sensor
	if(!oneWire_getResponse())
	{
		return 0; // If no response from DHT22, exit the function
	}

	for(uint8_t i = 0; i < 5; i++)
	{
		sensorData[i] = oneWire_read8();
	}

	return 1; // Return 1 if data is successfully read
}
//------------------------------------------------------------------------------
void dht22_setFields(dht22_t *sensor, uint8_t data[])
{
	sensor->rawTemp = (data[2] << 8) + data[3];
	sensor->temperature = calcTempr(sensor->rawTemp);
	sensor->rawHumidity = (data[0] << 8) + data[1];
	sensor->humidity = sensor->rawHumidity / 10.0f; // Convert to float
	sensor->checksum = data[4];
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