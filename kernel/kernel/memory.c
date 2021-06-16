#include "memory.h"
#include <stdint.h>

/* This file contains memory management functions for the kernel. */

extern __kernel_end;
unsigned int heap;

void *kmalloc(uint32_t size) {
  uint32_t ptr = __kernel_end + heap;
  heap += size;

  return (void *)ptr;
}

void kfree(void *addr) {
  // Do nothing
}
