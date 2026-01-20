#ifndef SED1565_C
#define SED1565_C
//------------------------------------------------------------------------------
#include "SED1565.h"
//------------------------------------------------------------------------------
void SED1565_init()
{
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

	SED1565_startLine(0);
	SED1565_command(bg_white);			// background: white
	SED1565_command(adc_normal);		// address counter: normal
	SED1565_command(display_on);
}
//------------------------------------------------------------------------------
void SED1565_data(uint8_t data)
{
  digitalWrite(RS, HIGH);       // RS = 1;  Data register  ( Strings and characters ).
  
  SED1565_transmit(data); 
}
//------------------------------------------------------------------------------
void SED1565_command(uint8_t command)
{
  digitalWrite(RS, LOW);        // RS = 0;  Instruction register ( commands ).
  
  SED1565_transmit(command); 
}
//------------------------------------------------------------------------------
void SED1565_startLine(uint8_t line)
{  
  SED1565_command( 0x40 | line); 
}
//------------------------------------------------------------------------------
void SED1565_setPosition(uint8_t page, uint8_t column)
{
	SED1565_command(0xB0 | (page & 0x0F));
	
	SED1565_command(0x10 | (column >> 4));		// High nibble
	SED1565_command(0x00 | (column & 0x0F));	// Low nibble
}
//------------------------------------------------------------------------------
void SED1565_print(uint8_t row, uint8_t col, uint8_t * text)
{
  SED1565_setPosition(row, col);  
  
  while(*text)
  {
		uint8_t chr = *text++;
		
		if(chr != 194)    // ° is implicitly split into 194 and 176 by the arduino c++ compiler
      writeChar(chr);
  }
}
//------------------------------------------------------------------------------
void SED1565_image(uint8_t *image)
{
  uint8_t *img;                     //Stores address of array elements of the image bitmap.
	uint8_t pg, col;
	
  for(pg = 0; pg < pgLen; pg++)
  {
    SED1565_setPosition(pg, 0);      //Pages: 0-7. Set once for each page then self increments in hardware.
		
    img = &image[pg*pgWidth];       //row*pgWidth: Offset value for start address to each "row" in image array. Alleviates need for 2-dimensional array.
    
		for(col = 0; col < pgWidth; col++) //Columns: 0 - 131...since 132 x 64
    {
      SED1565_data( img[col] );     //Dereference the address (via "[]") to get actual value at that postion.
    }
  }
}
//------------------------------------------------------------------------------
void SED1565_transmit(uint8_t data)
{
  uint8_t pinBits[8];
   
  SED1565_getBits(pinBits, data);
  SED1565_sendBits(pinBits);
}
//------------------------------------------------------------------------------
void SED1565_sendBits(uint8_t pinBit[])
{
  digitalWrite(D0, pinBit[0]);   //  D0 = pinBit[0];
  digitalWrite(D1, pinBit[1]);   //  D1 = pinBit[1];
  digitalWrite(D2, pinBit[2]);   //  D2 = pinBit[2];
  digitalWrite(D3, pinBit[3]);   //  D3 = pinBit[3];

  digitalWrite(D4, pinBit[4]);   //  D4 = pinBit[4];
  digitalWrite(D5, pinBit[5]);   //  D5 = pinBit[5];
  digitalWrite(D6, pinBit[6]);   //  D6 = pinBit[6];
  digitalWrite(D7, pinBit[7]);   //  D7 = pinBit[7];
  
  latch();
}
//------------------------------------------------------------------------------
void SED1565_getBits(uint8_t pinBit[], uint8_t data)
{ 
	uint8_t i;
  
	for(i = 0; i < 8; i++)
  {
    pinBit[i] = ((data >> i) & 0x01) ? 1 : 0;
  }
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr)
{
	uint8_t col, chunk;
	
	for(col = 0; col < 5; col++)
	{
		chunk = (isprint(chr)) ? chars[chr - ' '][col] : customChars[0][col];									
		SED1565_data(chunk);					
	}
		
	SED1565_data(0x00);						// Space 
}
//------------------------------------------------------------------------------
void latch()
{
  digitalWrite(EN, HIGH);       // EN  = 1;
  delay(1);
  digitalWrite(EN, LOW);        // EN  = 0;
	delay(1);
}
//------------------------------------------------------------------------------
#endif