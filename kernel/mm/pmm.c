#include <kernel/panic.h>
#include <kernel/pmm.h>
#include <kernel/vmm.h>
#include <stddef.h>

uint32_t pmm_stack_loc = PMM_STACK_ADDRESS;
uint32_t pmm_stack_max = PMM_STACK_ADDRESS;
uint32_t pmm_location;
int pmm_paging_active = 0;

uint32_t alloc_page_pmm() {
  if (pmm_paging_active) {
    if (pmm_stack_loc == PMM_STACK_ADDRESS) {
      panic("PMM: Out of memory");
    }

    pmm_stack_loc -= sizeof(uint32_t);
    uint32_t *stack = (uint32_t *)pmm_stack_loc;
    return *stack;
  } else {
    return pmm_location += 0x1000;
  }
}

void free_page_pmm(uint32_t page) {
  if (page < pmm_location) {
    return;
  }

  if (pmm_stack_max <= pmm_stack_loc) {
    map_vmm(pmm_stack_max, page, PAGE_PRESENT | PAGE_WRITE);
    pmm_stack_max += 4096;
  } else {
    uint32_t *stack = (uint32_t *)pmm_stack_loc;
    *stack = page;
    pmm_stack_loc += sizeof(uint32_t);
  }
}

void init_pmm(uint32_t start) {
  pmm_location = (start + 0x1000) & PAGE_MASK;
}
