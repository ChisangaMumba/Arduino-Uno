#ifndef DS3234_H
#define	DS3234_H
//------------------------------------------------------------------------------
#include "../SPI/soft_SPI.h"
//------------------------------------------------------------------------------
#define read_cmd                     0x00
#define write_cmd                    0x80
//------------------------------------------------------------------------------
#define control_reg                  0x0E
#define status_reg                   0x0F
//------------------------------------------------------------------------------
void DS3234_init();
uint8_t DS3234_read(uint8_t addr);
void DS3234_write(uint8_t addr, uint8_t data);
void DS3234_setTime(uint8_t time[]);
void DS3234_getTime(uint8_t time[]);
uint8_t calc_DecTime(uint8_t time);
uint8_t calc_BCDTime(uint8_t time);
//------------------------------------------------------------------------------
#endif