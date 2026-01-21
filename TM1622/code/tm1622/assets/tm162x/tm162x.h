#ifndef TM162x_H
#define TM162x_H
//-----------------------------------------------------------------------------------
#include "../serial/serial.c"
#include "chars.h"
//-----------------------------------------------------------------------------------
#define CMD_SYS_DIS             0x00    // (0000-0000-X) Turn off system oscillator, LCD bias generator
#define CMD_SYS_EN              0x01    // (0000-0001-X) Turn on  system oscillator
#define CMD_LCD_OFF             0x02    // (0000-0010-X) Turn off LCD display 
#define CMD_LCD_ON              0x03    // (0000-0011-X) Turn on  LCD display
#define CMD_TIMER_DIS           0x04    // (0000-0100-X) Disable time base output  
#define CMD_WDT_DIS             0x05    // (0000-0101-X) Disable WDT time-out flag output
#define CMD_TIMER_EN            0x06    // (0000-0110-X) Enable time base output 
#define CMD_WDT_EN              0x07    // (0000-0111-X) Enable WDT time-out flag output
#define CMD_TONE_OFF            0x08    // (0000-1000-X) Turn off tone outputs
#define CMD_CLR_TIMER           0x0D    // (0000-1101-X) Clear the contents of the time base generator
#define CMD_CLR_WDT             0x0F    // (0000-1111-X) Clear the contents of WDT stage          
#define CMD_RC_32K              0x18    // (0001-10XX-X) System clock source, on-chip RC oscillator
#define CMD_EXT_32K             0x1C    // (0001-11XX-X) System clock source, external clock source
#define CMD_BIAS_COM            0x29    // BIAS & COM (0010-10X1-X) 1/3 bias, 4 commons // HT1621 only
#define CMD_TONE_4K             0x40    // (010X-XXXX-X) Tone frequency output: 4kHz
#define CMD_TONE_2K             0x60    // (0110-XXXX-X) Tone frequency output: 2kHz
#define CMD_IRQ_DIS             0x80    // (100X-0XXX-X) Disable IRQ output
#define CMD_IRQ_EN              0x88    // (100X-0XXX-X) Enable IRQ output
#define CMD_F1                  0xA0    // (101X-0000-X) Time base clock output: 1Hz, The WDT time-out flag after: 4s
#define CMD_F2                  0xA1    // (101X-0001-X) Time base clock output: 2Hz, The WDT time-out flag after: 2s
#define CMD_F4                  0xA2    // (101X-0010-X) Time base clock output: 4Hz, The WDT time-out flag after: 1s
#define CMD_F8                  0xA3    // (101X-0011-X) Time base clock output: 8Hz, The WDT time-out flag after: 1/2s
#define CMD_F16                 0xA4    // (101X-0100-X) Time base clock output: 16Hz, The WDT time-out flag after: 1/4s
#define CMD_F32                 0xA5    // (101X-0101-X) Time base clock output: 32Hz, The WDT time-out flag after: 1/8s
#define CMD_F64                 0xA6    // (101X-0110-X) Time base clock output: 64Hz, The WDT time-out flag after: 1/16s
#define CMD_F128                0xA7    // (101X-0111-X) Time base clock output: 128Hz, The WDT time-out flag after: 1/32s
#define CMD_TEST_MODE           0xE0    // (1110-0000-X) Test mode
#define CMD_NORMAL_MODE         0xE3    // (1110-0011-X) Normal mode

#define CLEAR                   0x00
#define SET                     0xFF
//-----------------------------------------------------------------------------------
void TM162x_init(void);
void TM162x_command(uint8_t command);
void TM162x_data(uint8_t reg, uint8_t sdata, uint8_t noBits);
void TM162x_setDisplay(uint8_t sdata);
void TM162x_print(uint8_t text[]);
void writeChar(uint8_t nibbleAddr, uint8_t chr);
//-----------------------------------------------------------------------------------
#endif