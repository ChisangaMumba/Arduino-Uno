#ifndef  DS1620_C
#define  DS1620_C
//------------------------------------------------------------------------------
#include "ds1620.h"
//------------------------------------------------------------------------------
void  ds1620_init(int8_t lowTempr = 0, int8_t highTempr = 12)  //Defualt parameters only available in C++ 
{
	threeWire_init();
	ds1620_writeConfig(0x0A);

	// Set thermostat high and low values (entirely optional)
	ds1620_writeT_HL(WRITE_TH, highTempr);
	ds1620_writeT_HL(WRITE_TL, lowTempr);
}
//------------------------------------------------------------------------------
void ds1620_convert(uint8_t command)
{
	threeWire_start();
	threeWire_write(command, 8);
	threeWire_stop();
}
//------------------------------------------------------------------------------
int16_t ds1620_read(uint8_t command)
{
	int16_t data = 0;

	threeWire_start();
	threeWire_write(command, 8);
	// delay(750);			// Max conversion delay is 750ms according to the datasheet. uncomment after testing 
	data = threeWire_read();
	threeWire_stop();

	return data;
}
//------------------------------------------------------------------------------
void ds1620_writeT_HL(uint8_t command, int8_t data)
{	
	threeWire_start();
	
	threeWire_write(command, 8);
	threeWire_write(data << 1, 16);
	delay(20);

	threeWire_stop();
}
//------------------------------------------------------------------------------
uint8_t ds1620_writeConfig(uint8_t data)
{
	if(data > 0) 
	{
		threeWire_start();
		threeWire_write(WRITE_CONFIG, 8);
		threeWire_write(data, 8);
		delay(50);
		threeWire_stop();
				
		if(ds1620_read(READ_CONFIG) == data)
		{ 
			return WRITE_SUCCESSFUL;
		}
		else 
            { 
            	return WRITE_UNSUCCESSFUL;
            }
	}
	
	return BAD_CONFIG;
}
//------------------------------------------------------------------------------
int16_t calcTempr(int16_t tempr)
{
	int16_t num = (tempr >> 1);	//Discard LSByte (Only holds fraction flag _bit - see datasheet)

	if(tempr & 0x0100)			//if 9th _bit is a 1, num is negative - 2's complement (see datasheet)
	{
		num = -128 + (num & 0x7f);
	}

	return (num);	
}	
//------------------------------------------------------------------------------
#endif							//ds1620.C