#include <asm/asm.h>
#include <kernel/ports.h>
#include <stdint.h>

uint8_t inp(unsigned short port) {
  unsigned char c;
  _asm("inb %1, %0" : "=a"(c) : "dN"(port));
}

void outp(unsigned short port, unsigned char data) {
  _asm("outb %1, %0" : : "dN"(port), "a"(data));
}
