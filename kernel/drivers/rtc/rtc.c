#include <kernel/ports.h>
#include <rtc/rtc.h>
#include <kernel/nmi.h>
#include <cpu/irq.h>
#include <asm.h>

void init_rtc(void) {
  _asm("cli");
  nmi_disable();
  outp(0x71, 0x20);
  nmi_enable();
  _asm("sti");
  install_irq_handler(8, handler_rtc);
}

void handler_rtc(void) {
  // nothing yet
}
