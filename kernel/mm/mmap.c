#include <kernel/mmap.h>
#include <kernel/panic.h>
#include <kernel/printm.h>
#include <stdint.h>

void verify_mmap(multiboot_info_t *mboot_info) {
  if (!(mboot_info->flags >> 6 & 0x1)) {
    panic("Invalid Memory Map given\n");
  }
}

void print_mmap(multiboot_info_t *mboot_info) {
  if (!mboot_info) {
    return;
  }

  verify_mmap(mboot_info);

  printm("Memory info: \n");

  for (int i = 0; i < mboot_info->mmap_length;
       i += sizeof(multiboot_memory_map_t)) {
    multiboot_memory_map_t *mmap =
        (multiboot_memory_map_t *)(mboot_info->mmap_addr + i);

    printm("Start Addr: 0x%x | Length: 0x%x | Size: 0x%x | Type: ", mmap->addr,
           mmap->len, mmap->size);

    if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
      printm("Free\n");
    } else if (mmap->type == MULTIBOOT_MEMORY_RESERVED) {
      printm("Reserved\n");
    } else if (mmap->type == MULTIBOOT_MEMORY_ACPI_RECLAIMABLE) {
      printm("ACPI Reclaimable\n");
    } else if (mmap->type == MULTIBOOT_MEMORY_NVS) {
      printm("NVS\n");
    } else if (mmap->type == MULTIBOOT_MEMORY_BADRAM) {
      printm("Badram\n");
    } else {
      printm("Unknown\n");
    }
  }
}
