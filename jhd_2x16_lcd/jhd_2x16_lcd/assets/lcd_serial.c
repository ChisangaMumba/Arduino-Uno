#ifndef LCD_SERIAL_C
#define LCD_SERIAL_C
//------------------------------------------------------------------------------
#include "i2c.h"
#include "LCD_Serial.h"
//--------------------------------JHD1214---------------------------------------
void LCD_init()
{
  delay(30);    //Wait for more than 30ms after Vdd rises to 4.5v           
	
  I2C_init();     
  
  I2C_start();              
  I2C_write(DEV_ADDR);             
  
  LCD_command(home);
  LCD_command(function_set4);
  LCD_command(font2a);
  LCD_command(display_on);
  LCD_command(clear); 
	
  I2C_stop();
}
//------------------------------------------------------------------------------
void LCD_command(uint8_t data_)
{
	I2C_write(CMD_REG);				 //C0 = 1 RS = 0 (Instruction Register ( commands ))
	I2C_write(data_);
}
//------------------------------------------------------------------------------
void LCD_setPos(uint8_t data_)
{
	I2C_start();              
	I2C_write(DEV_ADDR); 
	
    LCD_command(data_);  
	
	I2C_stop();
}
//------------------------------------------------------------------------------
void LCD_string(uint8_t row, uint8_t col, uint8_t * text)
{
	LCD_setPos(RowAddr[row] + col);
	
	I2C_start(); 
	
	I2C_write(DEV_ADDR); 
	I2C_write(DAT_REG);			//C0 = 0 RS = 0 Data Register (Strings and characters).	
	while(*text)
	{
		uint8_t chr = *text++;
		

		if(chr == 176)    // 176 is ° in Extended ascii
			chr = 0xDF;   //223d is the value of ° symbol in Hitachi HD44780 LCDs
		
		if(chr != 194)	  //° is implicitly split into 194 and 176 by the arduino c++ compiler
			I2C_write(chr);
		
	}
	
	I2C_stop();
}
//------------------------------------------------------------------------------
#endif