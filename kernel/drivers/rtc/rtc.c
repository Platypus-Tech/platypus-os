#include <ports/ports.h>
#include <rtc/rtc.h>
#include <kernel/nmi.h>
#include <cpu/irq.h>
#include <asm.h>

void init_rtc(void) {
  install_irq_handler(8, handler_rtc);
}

void handler_rtc(void) {
  // nothing yet
}
