#include "panic.h"
#include <stdint.h>
#include <terminal/terminal.h>
#include <vga/vga.h>

extern const char *cmd;

void panic(const char *panicmessage) {
  cls();
  /* Colors influenced by Windows *eek* */
  settextcolor(COLOR_BLUE, COLOR_WHITE);

  /* This is based on Linux */
  writestr("Kernel Panic: not syncing, %s\n", panicmessage);
  writestr("Command - %s\n", cmd);
  writestr("---[end Kernel Panic: not syncing, %s ]---", panicmessage);

  /* Disable the interrupts */
  __asm__ volatile("cli");

  /* Halt the CPU */
  __asm__ volatile("hlt");
}
