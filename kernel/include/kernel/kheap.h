#ifndef _KERNEL_KHEAP_H
#define _KERNEL_KHEAP_H

#include <stdint.h>

#define HEAP_START 0xD0000000
#define HEAP_END 0xFFBFF000

typedef struct header {
  struct header *prev, *next;
  uint32_t allocated : 1;
  uint32_t length : 31;
} header_t;

void alloc_chunk(uint32_t start, uint32_t len);
void free_chunk(header_t *chunk);
void split_chunk(header_t *chunk, uint32_t len);
void glue_chunk(header_t *chunk);
void *kmalloc(uint32_t l);
void kfree(void *p);
void init_kheap();

#endif //_KERNEL_KHEAP_H
