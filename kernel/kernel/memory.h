#ifndef _SYSTEM_MEMORY_H
#define _SYSTEM_MEMORY_H

#include <stdint.h>

typedef long align;

union block_header {
  struct {
    union block_header *ptr;
    unsigned block_size;
  } s;
  align x;
};

typedef union block_header blk_hdr;

void *kmalloc(uint32_t size);
void kfree(void *addr);
void *malloc(unsigned int size);
static blk_hdr *mcore(unsigned units);

#endif //_SYSTEM_MEMORY_H
