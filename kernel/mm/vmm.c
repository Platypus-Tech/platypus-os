#include <kernel/panic.h>
#include <kernel/pmm.h>
#include <kernel/printm.h>
#include <kernel/vmm.h>
#include <string.h>

uint32_t *page_directory = (uint32_t *)PAGE_DIR_VIRT_ADDR;
uint32_t *page_tables = (uint32_t *)PAGE_TABLE_VIRT_ADDR;

page_dir_t *current_directory;

extern int pmm_paging_active;

void map_vmm(uint32_t va, uint32_t pa, uint32_t flags) {
  uint32_t virt_page = va / 0x1000;
  uint32_t pt_idx = PAGE_DIR_IDX(virt_page);

  if (page_directory[pt_idx] == 0) {
    page_directory[pt_idx] = alloc_page_pmm() | PAGE_PRESENT | PAGE_WRITE;
    memset(page_tables[pt_idx], 0, 0x1000);
  }

  page_tables[virt_page] = (pa & PAGE_MASK) | flags;
}

void unmap_vmm(uint32_t va) {
  uint32_t virt_page = va / 0x1000;
  page_tables[virt_page] = 0;
  __asm__ volatile("invlpg (%0)" : : "a"(va));
}

void switch_page_dir(page_dir_t *dir) {
  current_directory = dir;
  __asm__ volatile("mov %0, %%cr3" : : "r"(dir));
}

int get_mapping_vmm(uint32_t va, uint32_t *pa) {
  uint32_t virt_page = va / 0x1000;
  uint32_t pt_idx = PAGE_DIR_IDX(virt_page);

  if (page_directory[pt_idx] == 0) {
    return 0;
  }

  if (page_tables[virt_page] != 0) {
    if (pa) {
      *pa = page_tables[virt_page] & PAGE_MASK;
    }
    return 1;
  }
}

void init_vmm() {
  uint32_t cr0;

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

  __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
  cr0 |= 0x80000000;
  __asm__ volatile("mov %0, %%cr0" : : "r"(cr0));

  uint32_t pt_idx = PAGE_DIR_IDX((PMM_STACK_ADDRESS >> 12));
  page_directory[pt_idx] = alloc_page_pmm() | PAGE_PRESENT | PAGE_WRITE;
  memset(page_tables[pt_idx * 1024], 0, 0x1000);

  pmm_paging_active = 1;
}

void page_fault(struct registers *regs) {
  uint32_t cr2;
  __asm__ volatile("mov %%cr2, %0" : "=r"(cr2));
  printm("Page fault at 0x%x, faulting address 0x%x\n", regs->eip, cr2);
  printm("Error code: 0x%x\n", regs->err_code);
  int present = !(regs->err_code & 0x1);
  int rw = regs->err_code & 0x2;
  int user = regs->err_code & 0x4;
  int reserved = regs->err_code & 0x8;
  int id = regs->err_code & 0x10;

  printm("Page was ");

  if (present) {
    printm("present ");
  }
  if (rw) {
    printm("read-only ");
  }
  if (user) {
    printm("user-mode ");
  }
  if (reserved) {
    printm("reserved");
  }

  printm("\n");
  panic("Page fault");
}
