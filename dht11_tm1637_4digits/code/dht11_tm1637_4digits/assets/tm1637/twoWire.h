#ifndef  TWO_WIRE_H
#define  TWO_WIRE_H
//------------------------------------------------------------------------------
uint8_t CLK = 13;  // Clock pin
uint8_t DIO = 12;  // Data pin
//------------------------------------------------------------------------------
void twoWire_init()
{  
  pinMode(CLK, OUTPUT);

  digitalWrite(CLK, LOW);   //CLK = 0
  pinMode(DIO, OUTPUT);	    //DIO = 0
}
//------------------------------------------------------------------------------
void twoWire_start()
{
  digitalWrite(CLK, HIGH);	//CLK = 1;
  pinMode(DIO, INPUT);	    //DIO = 1;
  delayMicroseconds(2);
  pinMode(DIO, OUTPUT);	    //DIO = 0;
}
//------------------------------------------------------------------------------
void twoWire_stop()
{
  digitalWrite(CLK, LOW);	  //CLK = 0;
  delayMicroseconds(2);
  pinMode(DIO, OUTPUT);	    //DIO = 0;
  delayMicroseconds(2);
  digitalWrite(CLK, HIGH);	//CLK = 1;
  delayMicroseconds(2);
  pinMode(DIO, INPUT);      //DIO = 1;
}
//------------------------------------------------------------------------------
void twoWire_ack()
{
  digitalWrite(CLK, LOW);	  //CLK = 0;
  delayMicroseconds(5);
  digitalWrite(CLK, HIGH);	//CLK = 1;
  delayMicroseconds(2);
  digitalWrite(CLK, LOW);	  //CLK = 0;
}
//------------------------------------------------------------------------------
void twoWire_write(uint8_t data)
{
  uint8_t tx;
	
  for(tx = 0 ; tx < 8 ; tx++)
  {
	  digitalWrite(CLK, LOW);		//CLK = 0;
	  pinMode(DIO, ((data >> tx) & 0x01) ? INPUT : OUTPUT);   //LSB first (Real 12c sends MSB first)   
	  digitalWrite(CLK, HIGH);	//CLK = 1;                    //Toggle CLK pin to latch data bit
    
    delayMicroseconds(6);
  }
}
//------------------------------------------------------------------------------
#endif  /* TWO_WIRE_H */