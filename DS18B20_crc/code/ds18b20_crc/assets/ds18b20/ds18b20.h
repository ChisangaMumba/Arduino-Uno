#ifndef DS18B20_H
#define	DS18B20_H
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
void ds18b20_init(uint8_t highTemp, uint8_t lowTemp, uint8_t res);
uint8_t ds18b20_start();
void ds18b20_writeBit(uint8_t data);
void ds18b20_writeByte(uint8_t data);
uint8_t ds18b20_readBit();
uint8_t ds18b20_readByte();
uint8_t ds18b20_command(uint8_t data);
uint8_t ds18b20_getData(uint8_t data[]);
float ds18b20_getTempr(uint8_t data[]);
int8_t ds18b20_getTH(uint8_t data[]);
int8_t ds18b20_getTL(uint8_t data[]);
uint8_t ds18b20_getConfig(uint8_t data[]);
uint8_t ds18b20_calcCRC(uint8_t data[]);
float toFloat(signed int tempr, uint8_t resInd);
//------------------------------------------------------------------------------
uint8_t DQ_PIN = 10;
float resValues[4] = { 0.5, 0.25, 0.125, 0.0625 }; // 2^(-1), 2^(-2), 2^(-3), 2^(-4)
//------------------------------------------------------------------------------
#endif	/* DS18B20_H */