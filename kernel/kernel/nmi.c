#include <kernel/io.h>
#include <kernel/nmi.h>

void nmi_enable() {
  outp(0x70, inp(0x70) & 0x7F);
}

void nmi_disable() {
  outp(0x70, inp(0x70) | 0x80);
}
