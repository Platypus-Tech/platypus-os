#ifndef _DRIVERS_RTC_H
#define _DRIVERS_RTC_H

typedef struct {
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char day_of_week;
  unsigned char day_of_month;
  unsigned char month;
  unsigned char year;
} time_t;

void init_rtc();
void handler_rtc();

#endif //_DRIVERS_RTC_H
