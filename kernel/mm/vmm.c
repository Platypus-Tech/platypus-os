#include "vmm.h"
#include "pmm.h"
#include <cpu/idt.h>
#include <cpu/irq.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <stdint.h>
#include <string.h>

/* Based on JamesM's kernel development tutorials */

extern char paging_active;
uint32_t *page_dir = (uint32_t *)PAGE_DIRECTORY_VIRTUAL_ADDRESS;
uint32_t *page_tables = (uint32_t *)PAGE_TABLE_VIRTUAL_ADDRESS;

page_dir_t *current_directory;

void init_vmm() {
  int i;
  uint32_t cr0;

  page_dir_t *pd = (page_dir_t *)pmm_page_alloc();

  memset(pd, 0, 0x1000);

  pd[0] = pmm_page_alloc() | PRESENT_PAGE | WRITE_PAGE;
  uint32_t *pt = (uint32_t *)(pd[0] & MASK_PAGE);
  for (i = 0; i < 1024; i++) {
    pt[i] = i * 0x1000 | PRESENT_PAGE | WRITE_PAGE;
  }

  pd[1022] = pmm_page_alloc() | PRESENT_PAGE | WRITE_PAGE;
  pt = (uint32_t *)(pd[1022] & MASK_PAGE);
  memset(pt, 0, 0x1000);

  pt[1023] = (uint32_t)pd | PRESENT_PAGE | WRITE_PAGE;
  pd[1023] = (uint32_t)pd | PRESENT_PAGE | WRITE_PAGE;

  switch_page_directory(pd);

  init_paging();

  // uint32_t pt_idx = PAGE_DIRECTORY_IDX((PMM_STACK_ADDRESS >> 12));
  // page_dir[pt_idx] = pmm_page_alloc() | PRESENT_PAGE | WRITE_PAGE;
  // memset(page_tables[pt_idx * 1024], 0, 0x1000);

  paging_active = 1;
}

void switch_page_directory(page_dir_t *pd) {
  current_directory = pd;
  __asm__ volatile("mov %0, %%cr3" : : "r"(pd));
}

void vmm_map(uint32_t va, uint32_t pa, uint32_t flags) {
  uint32_t virtual_page = va / 0x1000;
  uint32_t pt_idx = PAGE_DIRECTORY_IDX(virtual_page);

  if (page_dir[pt_idx] == 0) {
    page_dir[pt_idx] = pmm_page_alloc() | PRESENT_PAGE | WRITE_PAGE;
    memset(page_tables[pt_idx * 1024], 0, 0x1000);
  }

  page_tables[virtual_page] = (pa & MASK_PAGE) | flags;
}

void vmm_unmap(uint32_t va) {
  uint32_t virtual_page = va / 0x1000;

  page_tables[virtual_page] = 0;
  __asm__ volatile("invlpg (%0)" : : "a"(va));
}

char vmm_get_mapping(uint32_t va, uint32_t *pa) {
  uint32_t virtual_page = va / 0x1000;
  uint32_t pt_idx = PAGE_DIRECTORY_IDX(virtual_page);

  if (page_dir[pt_idx] == 0) {
    return 0;
  }

  if (page_tables[virtual_page] != 0) {
    if (pa) {
      *pa = page_tables[virtual_page] & MASK_PAGE;
    }
    return 1;
  }
}
