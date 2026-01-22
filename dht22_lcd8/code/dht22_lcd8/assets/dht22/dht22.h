#ifndef DHT22_H
#define	DHT22_H
//------------------------------------------------------------------------------
uint8_t DATA_PIN = 2; // Pin connected to DHT22 data pin
//------------------------------------------------------------------------------
typedef struct 
{
    uint16_t rawTemp;
    float    temperature;
	uint16_t rawHumidity;
	float    humidity;
    uint8_t  checksum;        
} dht22_t;
//------------------------------------------------------------------------------
void 	oneWire_start(void);			
uint8_t oneWire_getResponse(void);			
uint8_t oneWire_read8(void);		
uint8_t dht22_calcChecksum(uint8_t sensorData[]);
uint8_t dht22_isDataValid(uint8_t sensorData[]);
uint8_t dht22_getSensorData(uint8_t sensorData[]);
void 	dht22_setFields(dht22_t *sensor, uint8_t data[]);
float 	calcTempr(int16_t rawData);
//------------------------------------------------------------------------------
#endif