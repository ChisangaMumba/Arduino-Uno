#ifndef  DS1631_C
#define	DS1631_C
//------------------------------------------------------------------------------
#include "ds1631.h"
//------------------------------------------------------------------------------
void ds1631_init(int16_t tempH, int16_t tempL, uint8_t resolution)
{
   I2C_init(); 

   // Set thermostat
   ds1631_write2ByteReg(TH_REG, tempH);    // Thermostat High
   ds1631_write2ByteReg(TL_REG, tempL);    // Thermostat Low
   
	ds1631_config(resolution | POL_HIGH);   // Polarity High (Active High) Thermostate output
	ds1631_convertCmd(START_CONV);
   resNum = ds1631_getResolutionNum();
	ds1631_convDelay();     
}
//------------------------------------------------------------------------------
void ds1631_convDelay()
{
   switch(resNum) 
   {
      case(0): delay(94);  break;   //  9-bit res 93.75ms conversion time
      case(1): delay(188); break;   // 10-bit res 187.5ms conversion time
      case(2): delay(375); break;   // 11-bit res 375ms conversion time
      case(3): delay(750); break;   // 12-bit res (Power-up default) 750ms conversion time
   }
}
//----------------------------Setup Device--------------------------------------
void ds1631_config(uint8_t command)
{
   I2C_start(); 
      
   I2C_write( DS1631_ADDR + Wr ); 
   I2C_write( CONFIG_REG ); 
   I2C_write( command );       // Continuous conversion, Active high polarity
                              
   I2C_stop();
   
   delay(12);                  // 10ms delay is required between consecutive writes to config reg
}
//--------------------Start or stop tempr converstion---------------------------
void ds1631_convertCmd(uint8_t command)
{
   I2C_start();
    
   I2C_write( DS1631_ADDR + Wr );
   I2C_write( command );
	
   I2C_stop(); 
}
//------------------------------------------------------------------------------
uint8_t ds1631_read1ByteReg(uint8_t deviceReg)
{
   uint8_t data;
   
   I2C_start(); 	           
   	
   I2C_write( DS1631_ADDR + Wr );	    
   I2C_write( deviceReg );	    
   I2C_restart();	           
   I2C_write( DS1631_ADDR + Rd );	        
   data = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return data;  
}
//------------------------------------------------------------------------------
void ds1631_write2ByteReg(uint8_t deviceReg, uint16_t settings)
{   
   I2C_start(); 	           
   	
   I2C_write( DS1631_ADDR + Wr );	    
   I2C_write( deviceReg );	    
	I2C_write( settings );
	I2C_write( settings >> 8 );
                           
   I2C_stop();

   delay(12); 
}
//------------------------------------------------------------------------------
int ds1631_read2ByteReg(uint8_t deviceReg)
{
   uint8_t data[2];
   
   I2C_start(); 	           
   	
   I2C_write( DS1631_ADDR + Wr );	    
   I2C_write( deviceReg );	    
   I2C_restart();	           
   I2C_write( DS1631_ADDR + Rd );	    
   data[1] = I2C_read(ACK);     
   data[0] = I2C_read(NACK);    // Signal End of reception with NACK
	
   I2C_stop();	
   
   return ( (data[1] << 8) + data[0] );   //NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
uint8_t ds1631_getResolutionNum(void)
{
  uint8_t resNum = ds1631_read1ByteReg(CONFIG_REG);
  
	return (resNum & 0x0C) >> 2;
}
//------------------------------------------------------------------------------
float ds1631_getTemp(uint8_t regName)
{
   int16_t tempr = ds1631_read2ByteReg(regName);

   return toFloat(tempr, resNum);
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