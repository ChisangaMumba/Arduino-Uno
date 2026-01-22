#ifndef DS1822_H
#define	DS1822_H
//------------------------------------------------------------------------------
uint8_t DQ_PIN = 2;
//------------------------------------------------------------------------------
typedef struct 
{
    uint16_t rawTemp;
    float    temperature;
    int8_t   tempHigh;    // high temperature threshold
    int8_t   tempLow;     // low temperature threshold
    uint8_t  config;
    uint8_t  resIndex;   // resolution index
    uint8_t  crc;        
} ds1822_t;
//------------------------------------------------------------------------------
#define FRAC_FLAG           0x000F
#define SKIP_ROM            0xCC
#define START_CONVERSION    0x44
#define WRITE_SCRATCHPAD    0x4E
#define READ_SCRATCHPAD     0xBE
//------------------------------------------------------------------------------
#define RES_09_BIT          0x1F
#define RES_10_BIT          0x3F
#define RES_11_BIT          0x5F
#define RES_12_BIT          0x7F
//------------------------------------------------------------------------------
void ds1822_init(uint8_t highTemp, uint8_t lowTemp, uint8_t res);
uint8_t ds1822_start(void);
void ds1822_writeByte(uint8_t data);
uint8_t ds1822_readByte(void);
uint8_t ds1822_command(uint8_t data);
uint8_t ds1822_getData(uint8_t data[]);
uint8_t ds1822_calcCRC(uint8_t data[], uint8_t size);
uint8_t ds1822_isDataValid(uint8_t data[], uint8_t size);
void ds1822_setFields(ds1822_t *sensor, uint8_t data[]);
void ds1822_convDelay(uint8_t resInd);
float toFloat(int16_t rawTemp);
//------------------------------------------------------------------------------
#endif	/* DS1822_H */