#include <kernel/pmm.h>
#include <kernel/vmm.h>
#include <string.h>

uint32_t *page_dir = (uint32_t *)PAGE_DIR_VIRT_ADDR;
uint32_t *page_tables = (uint32_t *)PAGE_TABLE_VIRT_ADDR;

page_dir_t *current_dir;

extern int paging_active_pmm;

void map_vmm(uint32_t va, uint32_t pa, uint32_t flags) {
  uint32_t virt_page = va / 0x1000;
  uint32_t page_table_index = PAGE_DIR_INDEX(virt_page);

  if (page_dir[page_table_index] == 0) {
    page_dir[page_table_index] = alloc_page_pmm() | PAGE_PRESENT | PAGE_WRITE;
    memset(page_tables[page_table_index * 1024], 0, 0x1000);
  }

  page_tables[virt_page] = (pa & PAGE_MASK) | flags;
}

void unmap_vmm(uint32_t va) {
  uint32_t virt_page = va / 0x1000;
  page_tables[virt_page] = 0;
  __asm__ volatile("invlpg (%0)" : : "a"(va));
}

int get_mapping_vmm(uint32_t va, uint32_t *pa) {
  uint32_t virt_page = va / 0x1000;
  uint32_t page_table_index = PAGE_DIR_INDEX(virt_page);

  if (page_dir[page_table_index] == 0) {
    return 0;
  }

  if (page_tables[virt_page] != 0) {
    if (pa) {
      *pa = page_tables[virt_page] & PAGE_MASK;
      return 1;
    }
  }
}

void switch_page_dir(page_dir_t *pd) {
  current_dir = pd;
  __asm__ volatile("mov %0, %%cr3" : : "r"(pd));
}

void init_vmm() {
  page_dir_t *pd = (page_dir_t *)alloc_page_pmm();
  memset(pd, 0, 0x1000);

  pd[0] = alloc_page_pmm() | PAGE_PRESENT | PAGE_WRITE;
  uint32_t *pt = (uint32_t *)(pd[0] & PAGE_MASK);

  for (int i = 0; i < 1024; i++) {
    pt[i] = i * 0x1000 | PAGE_PRESENT | PAGE_WRITE;
  }

  pd[1022] = alloc_page_pmm() | PAGE_PRESENT | PAGE_WRITE;
  pt = (uint32_t *)(pd[1022] & PAGE_MASK);
  memset(pt, 0, 0x1000);

  pt[1023] = (uint32_t)pd | PAGE_PRESENT | PAGE_WRITE;
  pd[1023] = (uint32_t)pd | PAGE_PRESENT | PAGE_WRITE;

  switch_page_dir(pd);

  uint32_t cr0;
  __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
  cr0 |= 0x80000000;
  __asm__ volatile("mov %0, %%cr0" : : "r"(cr0));

  uint32_t pt_index = PAGE_DIR_INDEX((PMM_STACK_ADDRESS >> 12));
  page_dir[pt_index] = alloc_page_pmm() | PAGE_PRESENT | PAGE_WRITE;
  memset(page_tables[pt_index * 1024], 0, 0x1000);

  paging_active_pmm = 1;
}
