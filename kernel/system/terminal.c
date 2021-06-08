#include "terminal.h"
#include "vtconsole.h"
#include <kernel/ports.h>
#include <stdint.h>
#include <string.h>
#include <vga/vga.h>

extern *vtc;

void put_prompt() {
  writestr("you@platypusOS:# ");
}

void run_command(char input[]) {
  if (strcmp(input, "version") == 0) {
    writestr("Version 0.08-dev\n");
  } else if (strcmp(input, "help") == 0) {
    writestr("Commands - version reboot help uname\n");
  } else if (strcmp(input, "uname") == 0) {
    writestr("PlatypusOS\n");
  } else if (strcmp(input, "reboot") == 0) {
    reboot();
  } else if (strcmp(input, "\0") == 0) {

  } else {
    writestr("%s : command not found!\n", input);
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
