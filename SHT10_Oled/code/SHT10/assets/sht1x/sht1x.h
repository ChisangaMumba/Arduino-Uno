#ifndef SHT1x_H
#define	SHT1x_H
//------------------------------------------------------------------------------
// Define the SHT1x I/O pins (adjust as needed)
uint8_t 	SHT_CLK  = 10;  			// SHT10 clock
uint8_t 	SHT_DATA = 9;  			// SHT10 data_ (bidirectional)
//------------------------------------------------------------------------------
#define 	TEMP_CMD  					0x03
#define 	HUMD_CMD  					0x05
#define 	WR_STATUS_REG_CMD  			0x06
#define 	RD_STATUS_REG_CMD  			0x07
#define 	SOFT_RESET_CMD  			0x1E
#define 	TIMEOUT_LIMIT 				10000
//------------------------------------------------------------------------------
#define 	SHT_ACK  					0
#define 	SHT_NACK 					1
//------------------------------------------------------------------------------
void 		SBus_start(void);
uint8_t 	SBus_ack(uint8_t ack);
uint8_t 	SBus_write(uint8_t data_);
uint8_t 	SBus_read(uint8_t ack);
uint8_t 	SBus_waitForResult(void);
uint16_t 	SHT1x_read(uint8_t command);
float 		SHT1x_getTemp(void);
float 		SHT1x_getHumd(float tempr);
//------------------------------------------------------------------------------
#endif