#include <kernel/ports.h>
#include <rtc/rtc.h>
#include <kernel/nmi.h>
#include <cpu/irq.h>

void handler_rtc() {
  irq_disable();
  nmi_disable();
  outp(0x71, 0x20);
  irq_enable();
}

void init_rtc() {
  // IRQ handler for RTC ?
  // install_irq_handler(8, handler_rtc);
}

int rtc_get_seconds() {
  nmi_disable();
  outp(0x71, 0x00);
  int seconds = inp(0x71);
  return seconds;
}
