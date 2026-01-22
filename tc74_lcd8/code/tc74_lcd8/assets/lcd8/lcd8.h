#ifndef LCD8_H
#define	LCD8_H
//------------------------------------------------------------------------------
//  Control Pins
uint8_t RS = 13;                                                                   
uint8_t EN = 12; 

//  Data Pins
uint8_t D0 = 11;
uint8_t D1 = 10;
uint8_t D2 = 9;
uint8_t D3 = 8;
uint8_t D4 = 7;
uint8_t D5 = 6;
uint8_t D6 = 5;
uint8_t D7 = 4;
//------------------------------------------------------------------------------
//                             Transmission direction
//------------------------------------------------------------------------------
#define LSBFIRST  0
#define MSBFIRST  1
//------------------------------------------------------------------------------
#define display_on      0x0C      //Cursor OFF, Blink off
#define display_off     0x08
#define cursor_on       0x0E
#define cursor_blink    0x0F
#define home            0x02
#define clear           0x01
#define auto_increment  0x06
#define auto_decrement  0x04
#define function_set4   0x28       //DL = 0 <Data Lenghth> (4 bit mode). N = 1 <Num lines> (2 Lines).
#define function_set8   0x38       //function set: 8 bit data length, Two display lines
#define font2           function_set | 0x04     //Set bit 3 only.
//------------------------------------------------------------------------------
void lcd_init(void);
void lcd_transmit(uint8_t data);
void lcd_data(uint8_t data);
void lcd_command(uint8_t command);
void lcd_string(uint8_t row, uint8_t column, uint8_t text[]);
void lcd_sendBits(uint8_t data);
uint8_t getBit(uint8_t pos , uint8_t data, uint8_t dir = LSBFIRST);
void latch(void);
//------------------------------------------------------------------------------
uint8_t rowAddr[] = { 0x80, 0xC0, 0x94, 0xD4 };  
//------------------------------------------------------------------------------
#endif