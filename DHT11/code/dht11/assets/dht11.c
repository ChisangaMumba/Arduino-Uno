#ifndef DHT11_C
#define	DHT11_C
//------------------------------------------------------------------------------
uint8_t DATA_PIN = 8;
//------------------------------------------------------------------------------
void oneWire_start()			// Microcontroller send request
{
  pinMode(DATA_PIN, OUTPUT);

  digitalWrite(DATA_PIN, LOW);	
	delay(20);	                       // delayMiliseconds
  digitalWrite(DATA_PIN, HIGH);	
}
//------------------------------------------------------------------------------
unsigned char oneWire_getResponse()			
{
	unsigned char response = 0;
	
  pinMode(DATA_PIN, INPUT);

	while(digitalRead(DATA_PIN) == 1);     // wait for DHT11 low pulse
	while(digitalRead(DATA_PIN) == 0);     // wait for DHT11 high pulse
	while(digitalRead(DATA_PIN) == 1);     // wait for DHT11 low pulse
	
	response = 1;
	
	return response;
}
//------------------------------------------------------------------------------
unsigned char oneWire_readByte()		
{
	unsigned char i, dataByte = 0;	
	
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
unsigned char dht11_calcChecksum(unsigned char sensorData[])
{
	unsigned char i, checksum = 0;
	
	for(i = 0; i < 4; i++)
	{
		checksum += sensorData[i];
	}
	
	return checksum;
}
//------------------------------------------------------------------------------
unsigned char dht11_isChecksumInvalid(unsigned char sensorData[])
{
	unsigned char isInvalid = 0;
	
	if(dht11_calcChecksum(sensorData) != sensorData[4]) // sensorData[4] == checksum value
	{
		isInvalid = 1;
	}
	
	return isInvalid;
}
//------------------------------------------------------------------------------
signed int dht11_getTemperature(unsigned char sensorData[])
{
  signed int tempr = (sensorData[3] << 8) + sensorData[2];
    
  return tempr;
}
//------------------------------------------------------------------------------
int dht11_getHumidity(unsigned char sensorData[])
{
  int humidity = (sensorData[1] << 8) + sensorData[0];
    
  return humidity;
}
//------------------------------------------------------------------------------
void dht11_getSensorData(unsigned char sensorData[])
{
	unsigned char i;
	for(i = 0; i < 5; i++)
	{
		sensorData[i] = oneWire_readByte();
	}
}
//------------------------------------------------------------------------------
#endif