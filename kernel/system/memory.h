#ifndef _SYSTEM_MEMORY_H
#define _SYSTEM_MEMORY_H

#include <stdint.h>

void *malloc(uint32_t size);
void free(void *addr);

#endif //_SYSTEM_MEMORY_H
