#ifndef _KERNEL_VMM_H
#define _KERNEL_VMM_H

#include <stdint.h>

#define PAGE_DIRECTORY_VIRTUAL_ADDRESS 0xFFBFF000
#define PAGE_TABLE_VIRTUAL_ADDRESS 0xFFC00000
#define PAGE_DIRECTORY_IDX(x) ((uint32_t)x / 1024)
#define PAGE_TABLE_IDX(x) ((uint32_t)x % 1024)

#define PRESENT_PAGE 0x1
#define WRITE_PAGE 0x2
#define USER_PAGE 0x4
#define MASK_PAGE 0xFFFFF000

typedef uint32_t page_dir_t;

void switch_page_directory(page_dir_t *pd);
void vmm_map(uint32_t va, uint32_t pa, uint32_t flags);
void vmm_unmap(uint32_t va);
char vmm_get_mapping(uint32_t va, uint32_t *pa);
void init_vmm();

#endif //_KERNEL_VMM_H
