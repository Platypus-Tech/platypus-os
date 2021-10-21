#ifndef _KERNEL_PMM_H
#define _KERNEL_PMM_H

#include <init/multiboot.h>
#include <stdint.h>

#define PMM_STACK_ADDRESS 0xFF000000
#define PAGE_SIZE 4096

uint32_t alloc_page_pmm();
void free_page_pmm(uint32_t page);
void init_pmm(multiboot_info_t *mboot_info);

#endif //_KERNEL_PMM_H
