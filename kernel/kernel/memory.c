#include <kernel/memory.h>
#include <stdint.h>

/* This file contains memory management functions for the kernel. */

extern uint32_t __kernel_end;
unsigned int heap;

void *kmalloc(uint32_t size) {
  heap += size;
}

void kfree(void *addr) {
  // Do nothing
}
