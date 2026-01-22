#ifndef DHT11_H
#define	DHT11_H
//------------------------------------------------------------------------------
uint8_t DATA_PIN = 7; // Pin connected to DHT11 data pin
//------------------------------------------------------------------------------
typedef struct 
{
    int16_t  temperature;
	int16_t  humidity;
    uint8_t  checksum;        
} dht11_t;
//------------------------------------------------------------------------------
void 	oneWire_start(void);			
uint8_t oneWire_getResponse(void);			
uint8_t oneWire_read8(void);		
uint8_t dht11_calcChecksum(uint8_t sensorData[]);
uint8_t dht11_isDataValid(uint8_t sensorData[]);
uint8_t dht11_getSensorData(uint8_t sensorData[]);
void 	dht11_setFields(dht11_t *sensor, uint8_t data[]);
//------------------------------------------------------------------------------
#endif