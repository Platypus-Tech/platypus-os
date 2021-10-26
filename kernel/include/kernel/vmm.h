#ifndef _KERNEL_VMM_H
#define _KERNEL_VMM_H

#include <cpu/isr.h>
#include <stdint.h>

#define PAGE_DIR_VIRT_ADDR 0xFFBFF000
#define PAGE_TABLE_VIRT_ADDR 0xFFC00000
#define PAGE_DIR_IDX(x) ((uint32_t)x / 1024)
#define PAGE_TABLE_IDX(x) ((uint32_t)x % 1024)

#define PAGE_PRESENT 0x1
#define PAGE_WRITE 0x2
#define PAGE_USER 0x4
#define PAGE_MASK 0xFFFFF000

typedef uint32_t page_dir_t;

void init_vmm();
void switch_page_dir(page_dir_t *dir);
void map_vmm(uint32_t va, uint32_t pa, uint32_t flags);
void unmap_vmm(uint32_t va);
int get_mapping_vmm(uint32_t va, uint32_t *pa);
void page_fault(struct registers *regs);

#endif //_KERNEL_VMM_H
