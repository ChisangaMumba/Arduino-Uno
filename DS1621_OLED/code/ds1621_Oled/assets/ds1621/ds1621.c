#ifndef DS1621_C
#define	DS1621_C
//------------------------------------------------------------------------------
#include "ds1621.h"
#include "../i2c/i2c.h"
//------------------------------------------------------------------------------
void ds1621_init(uint8_t addr)
{
   I2C_init(); 

   ds1621_config(addr);
	ds1621_convertCmd(addr, START_CONV);
}
//----------------------------Setup Device--------------------------------------
void ds1621_config(uint8_t addr)
{
  I2C_start(); 
    
  I2C_write( addr + Wr ); 
  I2C_write( CONFIG_REG ); 
  I2C_write( CONT_CONV );       // Continuous conversion, Active high polarity
                           
  I2C_stop();
}
//--------------------Start or stop tempr converstion---------------------------
void ds1621_convertCmd(uint8_t addr, uint8_t command)
{
   I2C_start();
    
   I2C_write( addr + Wr );
   I2C_write( command );
	
   I2C_stop(); 
}
//------------------------------------------------------------------------------
uint8_t ds1621_read1ByteReg(uint8_t addr, uint8_t deviceReg)
{
   uint8_t data = 0;
   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( deviceReg );	    
   I2C_restart();	           
   I2C_write( addr + Rd );	        
   data = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return data;  
}
//------------------------------------------------------------------------------
void ds1621_write2ByteReg(uint8_t addr, uint8_t deviceReg, uint16_t settings)
{   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( deviceReg );	    
	I2C_write( settings >> 8);    //Higher byte
	I2C_write( settings );        //Lower byte
                           
   I2C_stop();
}
//------------------------------------------------------------------------------
int16_t ds1621_read2ByteReg(uint8_t addr, uint8_t deviceReg)
{
   uint8_t data[2] = {0, 0};
   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    	    
   I2C_write( deviceReg );	    
   I2C_restart();	           
   I2C_write( addr + Rd );	    
   data[1] = I2C_read(ACK);     
   data[0] = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return ( (data[1] << 8) + data[0] );   //NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
  float result = tempr >> 8;     //Get rid of lower 8 bits (Only contains Fraction bit)

  return (tempr & FRAC_FLAG) ? result + 0.5 : result;
}
//------------------------------------------------------------------------------
#endif