#include "multiboot.h"
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/irq.h>
#include <cpu/isr.h>
#include <initrd/initrd.h>
#include <kernel/log.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printm.h>
#include <kernel/task.h>
#include <keyboard/keyboard.h>
#include <pit/pit.h>
#include <rtc/rtc.h>
#include <serial/serial.h>
#include <sound/pcspkr.h>
#include <string.h>
#include <system/vtconsole.h>
#include <terminal/terminal.h>
#include <vfs/vfs.h>
#include <vga/vga.h>

extern vtconsole_t *vtc;
extern uint32_t placement_address;
extern void paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y);
extern void cursor_move_callback(vtconsole_t *vtc, vtcursor_t *cur);

uint32_t initial_esp;

void kernel_main(multiboot_info_t *mboot_info, uint32_t initial_stack) {
  initial_esp = initial_stack;

  /* Initialize VGA and Framebuffer */
  init_vga();
  init_framebuffer();

  /* Load GDT, IDT, ISR, IRQ */
  init_gdt();
  writestr("[OK] Load GDT\n");
  init_idt();
  writestr("[OK] Load IDT\n");
  init_isr();
  writestr("[OK] Load ISR\n");
  init_irq();
  irq_enable();
  writestr("[OK] Load IRQ\n");

  /* Load Drivers */
  init_pit(1000);
  init_keyboard();
  register_snd_driver();
  init_serial();
  // init_rtc();
  writestr("[OK] Load Drivers\n");

  uint32_t initrd = *((uint32_t *)mboot_info->mods_addr);
  uint32_t initrd_end = *(uint32_t *)(mboot_info->mods_addr + 4);
  placement_address = initrd_end;

  init_paging();
  init_tasking();

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
  print("\033[1;34mVersion: \033[1;31m0.10-rc1\n");
  writestr("Kernel command line: %s\n", mboot_info->cmdline);
  uint32_t memsize = (mboot_info->mem_lower + mboot_info->mem_upper) / 1024;
  writestr("Total memory: %d MB\n", memsize);
  writestr("Initrd at address: %x", initrd);
  writestr("\n\n");

  vfs_root = init_initrd(initrd);

  writestr("\n");
  init_terminal();
}
