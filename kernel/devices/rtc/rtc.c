#include "rtc.h"
#include <asm/io.h>
#include <log/log.h>
#include "../../interrupts/nmi.h"

void rtc_work() { 
    inb(0x70); // heck idk
}

void rtc_init() {
    nmi_disable();
    log(INFO, "RTC Initialized");
    rtc_work();
}

void rtc_driver() {
    rtc_init();
}
