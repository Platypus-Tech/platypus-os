#include <asm/asm.h>
#include <cpu/irq.h>
#include <kernel/printm.h>

int irq_is_enabled;

int irq_enable() {
  if (irq_is_enabled == 1) {
    printm(1, "irqs already enabled");
    return 1;
  }

  _asm("sti");
  irq_is_enabled = 1;
}
