#ifndef DS1631_C
#define DS1631_C
//------------------------------------------------------------------------------
#include "ds1631.h"
//------------------------------------------------------------------------------
void ds1631_init(uint8_t addr, uint8_t resolution)
{	
   I2C_init();  

	ds1631_config(addr, 0);
	delay(12);			//10ms delay is required between consecutive writes to config reg
	ds1631_config(addr, resolution);
	ds1631_convertCmd(addr, START_CONV);
	delay(750);    //12 _bit resolution requires 750ms conversion time, see datasheet
}
//----------------------------Setup Device--------------------------------------
void ds1631_config(uint8_t addr, uint8_t command)
{
  I2C_start(); 
    
  I2C_write( addr + Wr ); 
  I2C_write( CONFIG_REG ); 
  I2C_write( command );       // Continuous conversion, Active high polarity
                           
  I2C_stop();
}
//--------------------Start or stop tempr converstion---------------------------
void ds1631_convertCmd(uint8_t addr, uint8_t command)
{
   I2C_start();
    
   I2C_write( addr + Wr );
   I2C_write( command );
	
   I2C_stop(); 
}
//------------------------------------------------------------------------------
uint8_t ds1631_read1ByteReg(uint8_t addr, uint8_t deviceReg)
{
   uint8_t data;
   
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
void ds1631_write2ByteReg(uint8_t addr, uint8_t deviceReg, unsigned int settings)
{   
   I2C_start(); 	           
   	
   I2C_write( addr + Wr );	    
   I2C_write( deviceReg );	    
	I2C_write( settings >> 8);
	I2C_write( settings & 0x00ff);
                           
   I2C_stop();
}
//------------------------------------------------------------------------------
int16_t ds1631_read2ByteReg(uint8_t addr, uint8_t deviceReg)
{
   uint8_t data[2];
   
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
uint8_t ds1631_getResolutionNum(uint8_t addr)
{
   uint8_t resNum = ds1631_read1ByteReg(addr, CONFIG_REG);
  
	return (resNum & 0x0C) >> 2;
}
//------------------------------------------------------------------------------
float ds1631_getTemperature(uint8_t addr)
{
   int16_t rawtemp = ds1631_read2ByteReg(addr, TEMP_REG);
   uint8_t resNum = ds1631_getResolutionNum(addr);

   return toFloat(rawtemp, resNum);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr, uint8_t resInd)
{
  float result = (float)(tempr >> 8);     
  int16_t count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
      result += ((count >> (7-resInd)) * resValues[resInd]);
  }
  
	return result; 
}
//------------------------------------------------------------------------------
#endif