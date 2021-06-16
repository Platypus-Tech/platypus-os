#include "panic.h"
#include <vga/vga.h>

void panic(const char *panicmessage) {
  cls();
  settextcolor(COLOR_RED, COLOR_BLACK);

  /* This is based on Linux */
  writestr("Kernel Panic: not syncing, %s\n", panicmessage);
  writestr("---[end Kernel Panic: not syncing, %s ]---\n", panicmessage);

  /* Disable the interrupts */
  __asm__ volatile("cli");

  /* Halt the CPU */
  __asm__ volatile("hlt");
}
