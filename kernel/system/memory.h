#ifndef _SYSTEM_MEMORY_H
#define _SYSTEM_MEMORY_H

#include <stdint.h>

typedef long align;

union block_header {
  struct {
    union block_header *ptr;
    unsigned block_size;
  } s;
};

typedef union block_header blk_hdr;

void *malloc(uint32_t size);
void free(void *addr);

#endif //_SYSTEM_MEMORY_H
