#ifndef SED1565_C
#define SED1565_C
//------------------------------------------------------------------------------
#include "sed1565.h"
//------------------------------------------------------------------------------
void sed1565_init()
{
  SPI_init();

  pinMode(CS1, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(RST, OUTPUT);

	sed1565_reset();

  //See Datasheet for elaboration
  sed1565_startline(0);        //Start at line 0.
  sed1565_command(0xA6);       //Display: Normal.
  sed1565_command(0xA1);       //ADC (Address Counter) Selection: Normal.
  sed1565_command(0xAF);       //sed1565 On.
}
//---------------------------------------------------8-------------------------
void sed1565_command(uint8_t command)
{
  digitalWrite(RS, LOW);		 // A0  = 0;                 //Command.

  digitalWrite(CS1, LOW);    // CS1 = 0;
  SPI_write(command);
  digitalWrite(CS1, HIGH);   // CS1 = 1;
}
//------------------------------------------------------------------------------
void sed1565_data(uint8_t data_)
{
  digitalWrite(RS, HIGH);    // A0 = 1;                  //Data.

  digitalWrite(CS1, LOW);   // CS1 = 0;
  SPI_write(data_);
  digitalWrite(CS1, HIGH);  // CS1 = 1;
}
//------------------------------------------------------------------------------
void sed1565_fill(uint8_t fill)
{
	int16_t pg, col;
  
	for(pg = 0; pg < pgLen; pg++)
  {
    sed1565_page(pg);        //Set in software
    sed1565_column(0);       //Set to zero then increments automatically in Hardware
    for(col = 0; col < pgWidth; col++)
    {
      sed1565_data( fill );
    }
  }
}
//------------------------------------------------------------------------------
void sed1565_page(uint8_t pg)
{
  pg = page[pg];
  sed1565_command(pg);
}
//------------------------------------------------------------------------------
void sed1565_column(uint8_t column)
{
  //Split column to into Nibbles
  uint8_t lowerNibble =   column & 0x0F;         //Eliminate upper nibble. Retain lower nibble.
  uint8_t higherNibble =( column & 0xF0 ) >> 4;  //Eliminate lower nibble. Retain upper nibble and shift right.

  sed1565_command( 0x10 | higherNibble );      //Check SED1565 Datasheet for explanation
  sed1565_command( lowerNibble );
}
//-------------------------64 Lines: 0 - 63-------------------------------------
void sed1565_startline(uint8_t line)
{
  sed1565_command( 0x40 | line );              //See Datasheet
}
//------------------------------------------------------------------------------
void sed1565_setAddress(uint8_t page, uint8_t column)
{
  sed1565_page(page);
  sed1565_column(column);
}
//------------------------------------------------------------------------------
void sed1565_printf(uint8_t page, uint8_t column, uint8_t *text)
{	
	sed1565_setAddress(page, column);
	
  while(*text)
  {
    uint8_t chr = *text++;

    if(chr != 194)						// ° is implicitly split into 194 and 176 by the arduino c++ compiler
		  writeChar(chr);
  }
}
//------------------------------------------------------------------------------
void sed1565_image(uint8_t *image)
{
  uint8_t* img;                //Stores address of array elements of the image bitmap.
	uint8_t pg, col;
	
  for(pg = 0; pg < pgLen; pg++)
  {
    sed1565_setAddress(pg, 0);     //Pages: 0-7.
															 //Set once for each page then self increments in hardware.
		
    img = &image[pg*pgWidth];  //row*pgWidth: Offset value for start address to each "row" in image array. Alleviates need for 2-dimensional array.
    
		for(col = 0; col < pgWidth; col++) //Columns: 0 - 131...since 132 x 64
    {
      sed1565_data( img[col] );    //Dereference the address (via "[]") to get actual value at that postion.
    }
  }
}
//------------------------------------------------------------------------------
void sed1565_reset(void)
{
	digitalWrite(RST, LOW);   // RST = 0;
	delay(5);
	digitalWrite(RST, HIGH);  // RST = 1;
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr)
{
	uint8_t col, chunk;
	
	for(col = 0; col < 5; col++)
	{
		chunk = (isascii(chr)) ? chars[chr - ' '][col] : customChars[0][col];
		sed1565_data(chunk);
	}
	
	sed1565_data(0x00);
}
//------------------------------------------------------------------------------
#endif