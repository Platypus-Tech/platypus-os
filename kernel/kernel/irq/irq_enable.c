#include <cpu/irq.h>
#include <kernel/vga.h>

int irq_is_enabled = 0;
extern int irq_is_disabled;

int irq_enable() {
  if (irq_is_disabled == 0 && irq_is_enabled == 1) {
    writestr("irqs already enabled\n");
    return 1;
  }

  __asm__ volatile("sti");

  irq_is_disabled = 0;
  irq_is_enabled = 1;
}
