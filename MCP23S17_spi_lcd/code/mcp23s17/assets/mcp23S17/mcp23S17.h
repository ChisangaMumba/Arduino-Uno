#ifndef EXPANDER_PROTOTYPES_H
#define EXPANDER_PROTOTYPES_H
//------------------------------------------------------------------------------
#include "../SPI/Soft_SPI.h"
//-----------------------I/O Direction Registers(TRIS)--------------------------
#define IODIRA     0x00
#define IODIRB     0x01
//-----------------------General Purpose I/O------------------------------------
#define GPIOA      0x12   //Reading the GPIOn register reads the value on the port.
#define GPIOB      0x13
//-----------------------Output Latches-----------------------------------------
#define OLATA      0x14   //Writing to the OLATn register Writes to the associated port.
#define OLATB      0x15
//-----------------------W/R Control bytes--------------------------------------
#define WRITE      0x40   // 0b0100 + 0b000(Slave address) + 0b0(Write) => 0x40
#define READ       0x41
//---------------------------Input pin Bit postions------------------------------------
#define I0         0x01
#define I1         0x02
#define I2         0x04
#define I3         0x08
#define I4         0x10
#define I5         0x20
#define I6         0x40
#define I7         0x80
//-------------------------Function Prototypes----------------------------------
void EXPANDER_init(uint8_t portA, uint8_t portB);
void EXPANDER_write(uint8_t address, uint8_t _data);
uint8_t EXPANDER_read(uint8_t address);
//------------------------------------------------------------------------------
#endif