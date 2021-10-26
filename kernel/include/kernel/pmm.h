#ifndef _KERNEL_PMM_H
#define _KERNEL_PMM_H

#include <stdint.h>

#define PMM_STACK_ADDRESS 0xFF000000

uint32_t alloc_page_pmm();
void free_page_pmm(uint32_t page);
void init_pmm(uint32_t start);

#endif //_KERNEL_PMM_H
