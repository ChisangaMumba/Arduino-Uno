#ifndef SERIAL_H
#define SERIAL_H
//-----------------------------------------------------------------------------------
uint8_t CS   =  8;	// Chip Select  : Active Low 
uint8_t WR   =  9;	// Write (clock): Active Low 
uint8_t DATA = 10;  // DATA (DIO)
//-----------------------------------------------------------------------------------
#define LSBFIRST  0
#define MSBFIRST  1
//-----------------------------------------------------------------------------------
void    serialInit(void);
void    serialOut(uint8_t dir, uint8_t sdata, uint8_t noBits);
uint8_t serialIn(uint8_t dir);
//-----------------------------------------------------------------------------------
#endif