#ifndef  THREE_WIRE_H
#define  THREE_WIRE_H
//------------------------------------------------------------------------------
uint8_t DQ   = 4;
uint8_t CLK2 = 3;
uint8_t RST  = 2;
//------------------------------------------------------------------------------
void threeWire_init();
void threeWire_start();
void threeWire_stop();
int16_t threeWire_read();
void threeWire_write(int16_t data, uint8_t sz);
//------------------------------------------------------------------------------
void threeWire_init()
{
	pinMode(DQ, OUTPUT);                                               
	pinMode(CLK2, OUTPUT);             
	pinMode(RST, OUTPUT);       
}
//------------------------------------------------------------------------------
void threeWire_start()
{
	digitalWrite(RST, LOW);      // RST = 0;
	digitalWrite(CLK2, HIGH);    // CLK2 = 1;
	digitalWrite(RST, HIGH);     // RST = 1;
}
//------------------------------------------------------------------------------
void threeWire_stop()
{
    digitalWrite(RST, LOW);      // RST = 0;
}
//------------------------------------------------------------------------------
void threeWire_write(int16_t data, uint8_t sz)
{
	pinMode(DQ, OUTPUT);        

	for(uint8_t tx = 0; tx < sz; tx++)
	{
        digitalWrite(CLK2, LOW);     // CLK2 = 0;
        digitalWrite(DQ, ((data >> tx) & 0x01) ? HIGH : LOW);   //LSB first (Real 12c sends MSB first)
        digitalWrite(CLK2, HIGH);     // CLK2 = 1;
	}

	pinMode(DQ, INPUT);        
}
//------------------------------------------------------------------------------
int16_t threeWire_read()
{	
	int16_t data = 0;

    pinMode(DQ, INPUT);                 

	for(uint8_t rx = 0; rx < 9; rx++)
	{
        digitalWrite(CLK2, LOW);         // CLK2 = 0;
		data += digitalRead(DQ) << rx;
		digitalWrite(CLK2, HIGH);        // CLK2 = 1;
	}
	
	pinMode(DQ, OUTPUT);                

	return data;
}
//------------------------------------------------------------------------------
#endif                  //threeWire.h