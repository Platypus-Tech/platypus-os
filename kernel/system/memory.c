#include "memory.h"
#include <stdint.h>

extern __kernel_end;
unsigned int heap;

static blk_hdr base;
static blk_hdr *free_p = NULL;

void *malloc(unsigned int size) {
    blk_hdr *p, *prev_p;
    blk_hdr *mcore(unsigned);
    unsigned total_units;
    
    total_units = (size + sizeof(blk_hdr) -1) / sizeof(blk_hdr) + 1;
    
    if ((prev_p = free_p) == NULL) {
        base.s.ptr = free_p = prev_p = &base;
        base.s.size = 0;
    }
}

void free(void *addr) {
    // Do nothing
}
