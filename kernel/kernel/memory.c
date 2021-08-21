#include <kernel/memory.h>
#include <stdint.h>

unsigned int heap;

void *mem_alloc(uint32_t size) {
  heap += size;
}

void mem_free(void *addr) {
  // Do nothing
}
