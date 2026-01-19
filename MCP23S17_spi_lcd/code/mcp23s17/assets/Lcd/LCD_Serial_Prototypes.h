#ifndef LCD_SERIAL_PROTOTYPES_H
#define LCD_SERIAL_PROTOTYPES_H
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
char  RowAddr[] = {0x80,0xC0,0x94,0xD4}; //Row0-Row3
bit RS;
//----------------------------Enable is Bit 3-----------------------------------
#define EN_high         0x04           //0000 0100
#define EN_low          0xFB           //1111 1011
//------------------------------------------------------------------------------
void LCD_init(void);
void LCD_command(char command);
void LCD_data(char _data);
void LCD_string(char row, char col, char * text);
void LCD_transmit(char _data);
void LCD_sendNibble(char _data);
//------------------------------------------------------------------------------
#endif