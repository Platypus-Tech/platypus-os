#ifndef _KERNEL_MEMORY_H
#define _KERNEL_MEMORY_H

#include <stdint.h>

void *kmalloc(uint32_t size);
void kfree(void *addr);

#endif //_KERNEL_MEMORY_H
