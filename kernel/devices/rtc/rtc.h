#ifdef RTC_H
    #undef RTC_H
    #define RTC_H
#else
    #ifndef RTC_H
        #define RTC_H

#define YEAR 2021
struct rtc_drvr_platypusos{
    void rtc_init(void);
    void rtc_work(void);
}
