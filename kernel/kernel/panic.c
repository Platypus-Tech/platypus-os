#include "panic.h"
#include <stdint.h>
#include <terminal/terminal.h>
#include <vga/vga.h>

extern const char *cmd;

void panic(const char *panicmessage) {
  cls();
  settextcolor(COLOR_RED, COLOR_BLACK);

  /* This is based on Linux */
  writestr("Kernel Panic: not syncing, %s\n", panicmessage);
  writestr("Command - %s\n", cmd);
  writestr("---[end Kernel Panic: not syncing, %s ]---", panicmessage);

  /* Disable the interrupts */
  __asm__ volatile("cli");

  /* Halt the CPU */
  __asm__ volatile("hlt");
}
