#include "multiboot.h"
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/irq.h>
#include <cpu/isr.h>
#include <kernel/paging.h>
#include <kernel/printm.h>
#include <kernel/syscall.h>
#include <kernel/task.h>
#include <keyboard/keyboard.h>
#include <pit/pit.h>
#include <rtc/rtc.h>
#include <serial/serial.h>
#include <sound/pcspkr.h>
#include <tarfs/tarfs.h>
#include <terminal/terminal.h>
#include <vga/framebuffer.h>
#include <vga/vga.h>

extern uint32_t placement_address;
uint32_t initial_esp;

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
  writestr("0.10-rc1\n");
  reset_text_color();
  writestr("\n");
}

void kernel_main(multiboot_info_t *mboot_info, uint32_t initial_stack) {
  initial_esp = initial_stack;

  // Initialize VGA and Framebuffer
  init_vga();
  init_framebuffer();

  // Load GDT, IDT, ISR, IRQ
  init_gdt();
  init_idt();
  init_isr();
  init_irq();
  writestr("[OK] Load GDT, IDT, ISR and IRQ\n");

  // Load Drivers
  init_pit(1000);
  init_keyboard();
  register_snd_driver();
  init_serial();
  // init_rtc();
  writestr("[OK] Load Drivers\n");

  uint32_t initrd = *((uint32_t *)mboot_info->mods_addr);
  uint32_t initrd_end = *(uint32_t *)(mboot_info->mods_addr + 4);
  placement_address = initrd_end;

  // Initialize paging and tasking
  init_paging();
  init_tasking();
  writestr("[OK] Initialize paging and tasking\n");

  irq_enable();

  cls();
  welcome_screen();

  writestr("Kernel command line: %s\n", mboot_info->cmdline);
  uint32_t memsize = (mboot_info->mem_lower + mboot_info->mem_upper) / 1024;
  writestr("Total memory: %d MB\n", memsize);
  writestr("Initrd at address: %x", initrd);
  writestr("\n\n");

  init_tarfs(initrd);

  init_terminal();
}
