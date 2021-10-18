#ifndef _KERNEL_VMM_H
#define _KERNEL_VMM_H

#include <stdint.h>

#define PAGE_DIR_VIRT_ADDR 0xFFBFF000
#define PAGE_TABLE_VIRT_ADDR 0xFFC00000
#define PAGE_DIR_INDEX(x) ((uint32_t)x / 1024)
#define PAGE_TABLE_INDEX(x) ((uint32_t)x % 1024)

#define PAGE_PRESENT 0x1
#define PAGE_WRITE 0x2
#define PAGE_USER 0x4
#define PAGE_MASK 0xFFFFF000

typedef uint32_t page_dir_t;

void switch_page_dir(page_dir_t *pd);
void map_vmm(uint32_t va, uint32_t pa, uint32_t flags);
void unmap_vmm(uint32_t va);
int get_mapping_vmm(uint32_t va, uint32_t *pa);
void init_vmm();

#endif //_KERNEL_VMM_H
