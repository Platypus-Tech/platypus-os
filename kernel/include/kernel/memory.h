#ifndef _KERNEL_MEMORY_H
#define _KERNEL_MEMORY_H

#include <stdint.h>

void *mem_alloc(uint32_t size);
void mem_free(void *addr);

#endif //_KERNEL_MEMORY_H
