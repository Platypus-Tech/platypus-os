#ifndef _SYSTEM_MEMORY_H
#define _SYSTEM_MEMORY_H

#include <stdint.h>

void *kmalloc(uint32_t size);
void kfree(void *addr);

#endif //_SYSTEM_MEMORY_H
