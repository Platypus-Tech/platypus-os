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
  uint32_t memsize = (mboot_info->mem_lower + mboot_info->mem_upper) / 1024;
  writestr("Total memory: %d MB\n", memsize);

  writestr("\n\n");
  init_terminal();
}
