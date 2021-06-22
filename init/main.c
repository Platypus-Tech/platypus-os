#include "multiboot.h"
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/irq.h>
#include <cpu/isr.h>
#include <kernel/log.h>
#include <kernel/panic.h>
#include <kernel/pmm.h>
#include <kernel/vmm.h>
#include <keyboard/keyboard.h>
#include <pit/pit.h>
#include <printm/printm.h>
#include <sound/pcspkr.h>
#include <string.h>
#include <system/vtconsole.h>
#include <terminal/terminal.h>
#include <vga/vga.h>

extern *vtc;
extern void paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y);
extern void cursor_move_callback(vtconsole_t *vtc, vtcursor_t *cur);

void kernel_main(multiboot_info_t *mboot_info, unsigned int magic) {
  /* Initialize VGA */
  init_vga();

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    panic("Invalid magic number");
  }

  /* Load GDT, IDT, ISR, IRQ */
  init_gdt();
  writestr("[OK] Load GDT\n");
  init_idt();
  writestr("[OK] Load IDT\n");
  init_isr();
  writestr("[OK] Load ISR\n");
  init_irq();
  writestr("[OK] Load IRQ\n");

  /* Load VMM and PMM */
  init_pmm(mboot_info->mem_upper);
  writestr("[OK] Load PMM\n");
  init_vmm();
  writestr("[OK] Load VMM\n");

  /* Load Drivers */
  init_timer(1000);
  init_keyboard();
  register_snd_driver();
  writestr("[OK] Load Drivers\n");

  __asm__ volatile("sti");

  info_log("System Loaded\n");

  if (strcmp(mboot_info->cmdline, "withvtconsole") == 0) {
    vtc = vtconsole(VGA_SCREEN_WIDTH, VGA_SCREEN_HEIGHT, paint_callback,
                    cursor_move_callback);
  }

  print(
      "\033[1;33m -------------------------------------------------------------------\n");
  print(
      "\033[1;33m|                       Welcome to Platypus OS!                     |\n");
  print(
      "\033[1;33m -------------------------------------------------------------------\n");

  print(
      "\033[1;34mOS: \033[1;36mPlatypus OS \033[1;33mx86_32 \033[1;32mx86_64 \n");
  print("\033[1;34mKernel: \033[1;32mPlatypus\n");
  print("\033[1;34mVersion: \033[1;31m0.09-dev\n");
  writestr("Kernel command line: %s\n", mboot_info->cmdline);

  /* Print the memory mapping */
  writestr("Memory Mapping: \n");
  int i;
  for (i = 0; i < mboot_info->mmap_length;
       i += sizeof(multiboot_memory_map_t)) {
    multiboot_memory_map_t *mem_map =
        (multiboot_memory_map_t *)(mboot_info->mmap_addr + i);

    writestr("Start Address: %x | Length: %x | Size: %x | Type: ",
             mem_map->addr, mem_map->len, mem_map->size);

    if (mem_map->type == MULTIBOOT_MEMORY_AVAILABLE) {
      writestr("FREE\n");
    } else if (mem_map->type == MULTIBOOT_MEMORY_RESERVED) {
      writestr("RESERVED\n");
    } else if (mem_map->type == MULTIBOOT_MEMORY_ACPI_RECLAIMABLE) {
      writestr("ACPI RECLAIMABLE\n");
    } else if (mem_map->type == MULTIBOOT_MEMORY_NVS) {
      writestr("NVS\n");
    } else if (mem_map->type == MULTIBOOT_MEMORY_BADRAM) {
      writestr("BADRAM\n");
    } else {
      writestr("UNKNOWN\n");
    }
  }
  writestr("\n\n");
  init_terminal();
}
