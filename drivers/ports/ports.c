#include <ports.h>
#include <stdint.h>

uint8_t port_byte_in(unsigned short port) {
      unsigned char c;
      __asm__ volatile("inb %1, %0" : "=a" (c) : "dN" (port));
}

void port_byte_out(unsigned short port, unsigned char data) {
     __asm__ volatile("outb %1, %0" : : "dN" (port), "a" (data));
} 
