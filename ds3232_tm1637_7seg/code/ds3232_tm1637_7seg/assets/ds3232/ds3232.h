#ifndef DS3232_H
#define	DS3232_H
//------------------------------------------------------------------------------
#include "../i2c/i2c.h"
#include "time_functions.h"
//------------------------------------------------------------------------------
typedef struct 
{
  uint8_t isColonOn = 0;
  uint8_t time[12];   //string for time in BCD format
  uint8_t date[12];   //string for date in BCD format
  uint8_t second;     //second (0-59)
  uint8_t minute;     //minute (0-59)
  uint8_t hour;       //hour (0-23)
  uint8_t dayOfWeek;  //day of the week (1-7, 1=Sunday)
  uint8_t dayOfMonth; //month (1-31)
  uint8_t month;      //month (1-12)
  uint16_t year;      //year (e.g., 2023)
} time_t;
//------------------------------------------------------------------------------
#define WR            0
#define RD            1
//------------------------------------------------------------------------------
#define tempMSB_REG   0x11
#define tempLSB_REG   0x12
#define FRAC_FLAG	  0x00C0
//------------------------------------------------------------------------------
void ds3232_init(uint8_t time[]);
void ds3232_setDateTime(uint8_t time[]);
void ds3232_getDateTime(time_t *tm, uint8_t time[]);
uint8_t ds3232_read(uint8_t address);
void ds3232_setDateTimeObj(time_t *tm, uint8_t time[]);
uint16_t ds3232_getRawTemp(void);
float ds3232_getTemp(void);
float toFloat(int16_t rawData);
//------------------------------------------------------------------------------
#endif