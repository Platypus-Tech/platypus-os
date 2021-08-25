/* Real Time Clock, not Regional Transportation Commission of Southern Nevada
 * (Vegas moment) */

#ifndef _DRIVERS_RTC_H
#define _DRIVERS_RTC_H

void init_rtc();
void handler_rtc();
int rtc_get_seconds();
int rtc_get_minutes();
int rtc_get_hours();

#endif //_DRIVERS_RTC_H
