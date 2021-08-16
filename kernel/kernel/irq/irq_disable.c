#include <asm/asm.h>
#include <cpu/irq.h>
#include <vga/vga.h>

int irq_is_disabled = 0;
extern int irq_is_enabled;

int irq_disable() {
  if (irq_is_enabled == 1 && irq_is_disabled == 0) {
    writestr("irqs already disabled\n");
    return 1;
  }

  _asm("cli");
  irq_is_disabled = 1;
  return 0;
}
