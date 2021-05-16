#include "nmi.h"

void NMI_enable(void) {
    outb(0x70, inb(0x70) & 0x7F);
}

void NMI_disable(void) {
    outb(0x70, inb(0x70) | 0x80);
}
