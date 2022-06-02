#ifndef _KERNEL_RTC_H
#define _KERNEL_RTC_H

#include "io.h"

typedef struct {
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char month;
  unsigned char year;
} time_t;

void init_rtc();
void handler_rtc();
void gettime_rtc(time_t *time);

#endif //_KERNEL_RTC_H
