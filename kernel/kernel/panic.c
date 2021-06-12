#include "panic.h"
#include <vga/vga.h>

void panic(const char *panicmessage) {
  clearwin(COLOR_WHT, COLOR_BLK);
  putstr("Kernel Panic: ", COLOR_RED, COLOR_BLK);
  putstr(panicmessage, COLOR_RED, COLOR_BLK);

  /* Disable the interrupts */
  __asm__ volatile("cli");

  /* Halt the CPU */
  __asm__ volatile("hlt");
}
