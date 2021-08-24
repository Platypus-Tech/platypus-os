#include <rtc/rtc.h>
#include <cpu/irq.h>

void init_rtc(void) {
  install_irq_handler(8, handler_rtc);
}

void handler_rtc(void) {
  // nothing yet
}
