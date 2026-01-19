#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#define ACK  0
#define NACK 1
//------------------------------------------------------------------------------
uint8_t SCLK = 9;
uint8_t SDAT = 8;
//------------------------------------------------------------------------------
void I2C_init();
void I2C_start();
void I2C_restart();
void I2C_stop();
void I2C_ack(uint8_t ackn);
uint8_t I2C_write(uint8_t data);
uint8_t I2C_read(uint8_t ackState);
//------------------------------------------------------------------------------
#endif