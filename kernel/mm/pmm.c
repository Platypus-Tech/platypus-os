#include <kernel/panic.h>
#include <kernel/pmm.h>
#include <kernel/vmm.h>

uint32_t stack_location_pmm = PMM_STACK_ADDRESS;
uint32_t stack_max_pmm = PMM_STACK_ADDRESS;
uint32_t location_pmm;
int paging_active_pmm = 0;

uint32_t alloc_page_pmm() {
  if (paging_active_pmm) {
    if (stack_location_pmm == PMM_STACK_ADDRESS) {
      panic("PMM: Out of memory");
    }

    stack_location_pmm -= sizeof(uint32_t);
    uint32_t *stack = (uint32_t *)stack_location_pmm;
    return *stack;
  } else {
    location_pmm += 0x1000;
  }
}

void free_page_pmm(uint32_t page) {
  if (page < location_pmm) {
    return;
  }

  if (stack_max_pmm <= stack_location_pmm) {
    map_vmm(stack_max_pmm, page, PAGE_PRESENT | PAGE_WRITE);
    stack_max_pmm += 4096;
  } else {
    uint32_t *stack = (uint32_t *)stack_location_pmm;
    *stack = page;
    stack_location_pmm += sizeof(uint32_t);
  }
}

void init_pmm(multiboot_info_t *mboot_info) {
  uint32_t start = mboot_info->mem_upper;
  location_pmm = (start + 0x1000) & PAGE_MASK;

  uint32_t i = mboot_info->mmap_addr;
  while (i < mboot_info->mmap_addr + mboot_info->mmap_length) {
    multiboot_memory_map_t *entry = (multiboot_memory_map_t *)i;

    if (entry->type == MULTIBOOT_MEMORY_AVAILABLE) {
      for (uint32_t j = entry->addr; j < entry->addr + entry->len;
           j += 0x1000) {
        free_page_pmm(j);
      }
    }
    i += entry->size + sizeof(uint32_t);
  }
}
