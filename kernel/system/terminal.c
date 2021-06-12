#include "terminal.h"
#include "vtconsole.h"
#include <kernel/log.h>
#include <kernel/ports.h>
#include <stdint.h>
#include <string.h>
#include <vga/vga.h>

extern *vtc;

void put_prompt() {
  printm("you@platypusOS:# ");
}

void run_command(char input[]) {
  if (strcmp(input, "version") == 0) {
    printm("Version 0.08-dev\n");
  } else if (strcmp(input, "help") == 0) {
    printm("Commands - version reboot help log uname\n");
  } else if (strcmp(input, "uname") == 0) {
    printm("PlatypusOS\n");
  } else if (strcmp(input, "reboot") == 0) {
    reboot();
  } else if (strcmp(input, "log") == 0) {
    show_log();
  } else if (strcmp(input, "\0") == 0) {

  } else {
    printm(input);
    printm(" : command not found!\n");
  }

  for (int i = 0; input[i] != '\0'; i++) {
    input[i] = '\0';
  }

  put_prompt();
}

void reboot() {
  vtconsole_delete(vtc);
  uint8_t t = 0x02;
  while (t & 0x02) {
    t = inp(0x64);
  }
  outp(0x64, 0xFE);
  __asm__ volatile("hlt");
}

void init_terminal() {
  put_prompt();
}
