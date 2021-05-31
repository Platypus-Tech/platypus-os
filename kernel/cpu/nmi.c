#include "nmi.h"
#include <kernel/ports.h>

void nmi_enable(void) {
    outp(0x70, inp(0x70) & 0x7F);
}

void nmi_disable(void) {
    outp(0x70, inp(0x70) | 0x80);
}
