#ifndef SHT2x_C
#define SHT2x_C
//------------------------------------------------------------------------------
#include "sht2x.h"
//------------------------------------------------------------------------------
void SHT2x_init(void) 
{
    I2C_init();
}
//------------------------------------------------------------------------------
uint16_t SHT2x_read(uint8_t regAddress)
{
    uint8_t data[2] = { 0, 0};

    I2C_start();
    
    I2C_write(SHT21_I2C_ADDRESS + 0);
    I2C_write(regAddress);      //measurement command
    I2C_restart();
    I2C_write(SHT21_I2C_ADDRESS + 1) ;
    data[1] = I2C_read(ACK);    // MSB
    data[0] = I2C_read(NACK);   // LSB
    
    I2C_stop();

    return (data[1] << 8) + data[0];
}
//------------------------------------------------------------------------------
float SHT2x_getTemp()
{
    uint16_t rawTemp = SHT2x_read(TEMP_MEASURE);

    return (-46.85 + 175.72/65536 * (float)rawTemp);
}
//------------------------------------------------------------------------------
float SHT2x_getHumd()
{
    uint16_t rawHumd = SHT2x_read(HUMD_MEASURE);

    return (-6.0 + 125.0/65536 * (float)rawHumd);
}
//------------------------------------------------------------------------------
#endif