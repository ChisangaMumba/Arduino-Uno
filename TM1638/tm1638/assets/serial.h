#ifndef SERIAL_H
#define SERIAL_H
//-----------------------------------------------------------------------------------
void serialOut(uint8_t dir, uint8_t data);
uint8_t serialIn(uint8_t dir);
//-----------------------------------------------------------------------------------
void serialOut(uint8_t dir, uint8_t data)
{
  pinMode(DIO, OUTPUT); 
  
  for(uint8_t tx = 0; tx < 8; tx++)
  {
	digitalWrite(CLK, LOW);

	switch(dir)
	{
	  case(0): digitalWrite(DIO, ((data >> tx) & 0x01) ? HIGH : LOW); break; //LSB first
	  case(1): digitalWrite(DIO, ((data << tx) & 0x80) ? HIGH : LOW); break; //MSB first		
	}
	
	digitalWrite(CLK, HIGH);;
  }
}
//-----------------------------------------------------------------------------------
uint8_t serialIn(uint8_t dir)
{
  uint8_t data = 0;
  
  for(uint8_t Rx = 0; Rx < 8; Rx++)
  {
	digitalWrite(CLK, LOW);

	switch(dir)
	{
	  case(0): data += digitalRead(DIO) << Rx;     break;  //LSB first
	  case(1): data += digitalRead(DIO) << (7-Rx); break;  //MSB first		
	}
	
	digitalWrite(CLK, HIGH);
  }
  
  return data;
}
//-----------------------------------------------------------------------------------
#endif