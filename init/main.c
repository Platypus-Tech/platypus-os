#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/irq.h>
#include <cpu/isr.h>
#include <kernel/log.h>
#include <keyboard/keyboard.h>
#include <pit/pit.h>
#include <printm/printm.h>
#include <terminal/terminal.h>
#include <system/vtconsole.h>
#include <vga/vga.h>

extern *vtc;
extern void paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y);
extern void cursor_move_callback(vtconsole_t *vtc, vtcursor_t *cur);

void kernel_main() {

  /* Load GDT, IDT, ISR, IRQ and PIT */
  init_gdt();
  printm(0, "[OK] Load GDT\n");
  init_idt();
  printm(0, "[OK] Load IDT\n");
  init_isr();
  printm(0, "[OK] Load ISR\n");
  init_irq();
  printm(0, "[OK] Enable NMI\n");
  init_timer(50);
  printm(0, "[OK] Load PIT\n");

  /* Load Drivers */
  init_keyboard();
  printm(0, "[OK] Load Drivers\n");

  __asm__ volatile("sti");

  info_log("System Loaded\n");

  vtc = vtconsole(VGA_SCREEN_WIDTH, VGA_SCREEN_HEIGHT, paint_callback,
                  cursor_move_callback);

  print(
      "\033[1;33m -------------------------------------------------------------------\n");
  print(
      "\033[1;33m|                       WELCOME TO PLATYPUS OS                      |\n");
  print(
      "\033[1;33m -------------------------------------------------------------------\n");
  print(
      "\033[1;34mOS: \033[1;36mPlatypusOS \033[1;33mx86_32 \033[1;32mx86_64 \n");
  print("\033[1;34mKernel: \033[1;32mPlatypus\n");
  print("\033[1;34mVersion: \033[1;31m0.08-dev\n");
  putstr("\n", COLOR_WHT, COLOR_BLK);

  init_terminal();
}
