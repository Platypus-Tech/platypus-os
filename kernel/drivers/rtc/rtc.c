#include <kernel/ports.h>
#include <rtc/rtc.h>
#include <kernel/nmi.h>
#include <cpu/irq.h>
#include <asm/asm.h>

void handler_rtc(void) {
    _asm("cli");
  nmi_disable();
  outp(0x71, 0x20);
  nmi_enable();
  _asm("sti");
}

void init_rtc(void) {
  install_irq_handler(8, handler_rtc);
}
