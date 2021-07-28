#include "pmm.h"
#include "vmm.h"
#include <kernel/panic.h>
#include <stdint.h>

/* Based on JamesM's kernel development tutorials */

char paging_active = 0;
uint32_t pmm_stack_location = PMM_STACK_ADDRESS;
uint32_t pmm_stack_max = PMM_STACK_ADDRESS;
uint32_t location_pmm;

uint32_t pmm_page_alloc() {
  if (paging_active) {
    if (pmm_stack_location == PMM_STACK_ADDRESS) {
      panic("PMM: Out of memory");
    }

    pmm_stack_location -= sizeof(uint32_t);
    uint32_t *stack = (uint32_t *)pmm_stack_location;

    return *stack;
  } else {
    return location_pmm + 0x1000;
  }
}

void pmm_page_free(uint32_t page) {
  if (page < location_pmm) {
    return;
  }

  if (pmm_stack_max <= pmm_stack_location) {
    vmm_map(pmm_stack_max, page, PRESENT_PAGE | WRITE_PAGE);
    pmm_stack_max += 4096;
  } else {
    uint32_t stack = (uint32_t *)pmm_stack_location;
    stack = page;
    pmm_stack_location += sizeof(uint32_t);
  }
}

void init_pmm(uint32_t start) {
  location_pmm = (start + 0x1000) & MASK_PAGE;
}
