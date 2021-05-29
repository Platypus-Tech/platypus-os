#include "memory.h"
#include <stdint.h>

extern __kernel_end;
unsigned int heap;

void *malloc(unsigned int size) {
    uint32_t ptr = __kernel_end + heap;
    heap += size;
    
    return (void*)ptr;
}

void free(void *addr) {
    // Do nothing
}
