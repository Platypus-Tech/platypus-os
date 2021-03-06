#include "multiboot.h"
#include <assert.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/irq.h>
#include <cpu/isr.h>
#include <initrd/initrd.h>
#include <kernel/device.h>
#include <kernel/elf.h>
#include <kernel/floppy.h>
#include <kernel/keyboard.h>
#include <kernel/kheap.h>
#include <kernel/paging.h>
#include <kernel/pcspkr.h>
#include <kernel/pit.h>
#include <kernel/printm.h>
#include <kernel/rtc.h>
#include <kernel/serial.h>
#include <kernel/task.h>
#include <kernel/vfs.h>
#include <kernel/vga.h>
#include <terminal/terminal.h>

uint32_t initial_esp;
extern uint32_t placement_address;
elf_t kernel_elf;

void welcome_screen() {
  settextcolor(LIGHT_YELLOW, BLACK);
  writestr(
      " -------------------------------------------------------------------\n");
  writestr(
      "|                       Welcome to Platypus OS!                     |\n");
  writestr(
      " -------------------------------------------------------------------\n");
  settextcolor(BLUE, BLACK);
  writestr("OS: ");
  settextcolor(LIGHT_CYAN, BLACK);
  writestr("Platypus OS ");
  settextcolor(LIGHT_YELLOW, BLACK);
  writestr("x86_32 ");
  settextcolor(LIGHT_GREEN, BLACK);
  writestr("x86_64\n");
  settextcolor(BLUE, BLACK);
  writestr("Kernel: ");
  settextcolor(LIGHT_GREEN, BLACK);
  writestr("Platypus\n");
  settextcolor(BLUE, BLACK);
  writestr("Version: ");
  settextcolor(LIGHT_RED, BLACK);
  writestr("0.11-rc3\n");
  reset_text_color();
  writestr("\n");
}

void kernel_main(multiboot_info_t *mboot_info, uint32_t initial_stack) {
  initial_esp = initial_stack;

  init_vga();

  init_gdt();
  init_idt();
  init_isr();
  init_irq();
  printm("GDT, IDT, ISR and IRQ initialized\n");

  init_pit(100);
  init_keyboard();
  init_pcspkr();
  init_serial();
  init_rtc();
  printm("Drivers initialized\n");

  kernel_elf = elf_from_multiboot(mboot_info->u.elf_sec);

  ASSERT(mboot_info->mods_count > 0);
  uint32_t initrd = *((uint32_t *)mboot_info->mods_addr);
  uint32_t initrd_end = *(uint32_t *)(mboot_info->mods_addr + 4);
  placement_address = initrd_end;

  init_paging();
  init_tasking();
  printm("Paging and tasking initialized\n");

  init_device_manager();

  cls();
  welcome_screen();

  writestr("Kernel command line: %s\n", mboot_info->cmdline);
  uint32_t memsize = (mboot_info->mem_lower + mboot_info->mem_upper) / 1024;
  writestr("Total memory: %d MB\n", memsize);
  writestr("Initrd at address: %x\n", initrd);
  detect_drives_floppy();
  writestr("\n");

  vfs_root = init_initrd(initrd);

  init_terminal();
}
