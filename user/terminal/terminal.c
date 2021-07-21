#include "terminal.h"
#include <kernel/log.h>
#include <kernel/panic.h>
#include <kernel/ports.h>
#include <kernel/power.h>
#include <printm/printm.h>
#include <sound/pcspkr.h>
#include <stdint.h>
#include <string.h>
#include <vfs/vfs.h>
#include <vga/vga.h>

const char *cmd;

void put_prompt() {
  writestr("you@platypusOS:# ");
}

void run_command(char input[]) {
  cmd = input;
  if (strcmp(input, "version") == 0) {
    writestr("Version 0.09-dev\n");
  } else if (strcmp(input, "help") == 0) {
    writestr(
        "Commands - version reboot help log mount ls hello playsound stopsound panic uname\n");
  } else if (strcmp(input, "uname") == 0) {
    writestr("PlatypusOS\n");
  } else if (strcmp(input, "reboot") == 0) {
    reboot();
  } else if (strcmp(input, "ls") == 0) {
    ls();
  } else if (strcmp(input, "playsound") == 0) {
    beep();
  } else if (strcmp(input, "stopsound") == 0) {
    stop_sound();
  } else if (strcmp(input, "log") == 0) {
    show_log();
  } else if (strcmp(input, "panic") == 0) {
    panic("panic command used!");
  } else if (strcmp(input, "hello") == 0) {
    writestr("Hello to you too?\n");
  } else if (strcmp(input, "mount") == 0) {
    mount();
  } else if (strcmp(input, "\0") == 0) {

  } else {
    writestr("%s: command not found!\n", input);
  }

  for (int i = 0; input[i] != '\0'; i++) {
    input[i] = '\0';
  }

  put_prompt();
}

void init_terminal() {
  put_prompt();
}
