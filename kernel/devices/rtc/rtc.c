#include "rtc.h"
#include <asm/io.h>
#include <log/log.h>

struct rtc_drvr_platypusos rtc;

void rtc_driver(void){
    rtc.init();
    rtc.work();
}

void init(void){
    inb(0x70); // heck idk
}