#ifndef  TWO_WIRE_H
#define  TWO_WIRE_H
//------------------------------------------------------------------------------
uint8_t CLK = 9;
uint8_t DIO = 8;
//------------------------------------------------------------------------------
void twoWire_init();
void twoWire_start();
void twoWire_stop();
void twoWire_ack();
void twoWire_write(uint8_t data);
//------------------------------------------------------------------------------
#endif  /* TWO_WIRE_H */