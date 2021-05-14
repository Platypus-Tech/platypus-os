#include "rtc.h"
#include <asm/io.h>
#include <log/log.h>
#include "../../interrupts/nmi.h"

struct rtc_drvr_platypusos rtc;

void rtc_driver(void){
    rtc.init();
}

void init(void){
    nmi_disable();
    log(INFO, "RTC initialized!");
    rtc.work();
}

void work(void){
    inb(0x70); // heck idk
}
