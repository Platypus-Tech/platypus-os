#ifndef _KERNEL_KHEAP_H
#define _KERNEL_KHEAP_H

#include <stdint.h>

uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys);
uint32_t kmalloc_a(uint32_t sz);
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys);
uint32_t pmalloc(uint32_t sz);

#endif //_KERNEL_KHEAP_H
