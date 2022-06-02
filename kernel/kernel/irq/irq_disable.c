#include <cpu/irq.h>
#include <kernel/vga.h>

int irq_is_disabled = 0;
extern int irq_is_enabled;

int irq_disable() {
  if (irq_is_enabled == 0 && irq_is_disabled == 1) {
    writestr("irqs already disabled\n");
    return 1;
  }

  __asm__ volatile("cli");

  irq_is_enabled = 0;
  irq_is_disabled = 1;
}
