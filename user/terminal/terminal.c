#include "terminal.h"
#include <commands/commands.h>
#include <generated/config.h>
#include <kernel/panic.h>
#include <kernel/ports.h>
#include <kernel/power.h>
#include <sound/pcspkr.h>
#include <string.h>
#include <vfs/vfs.h>
#include <vga/vga.h>

void put_prompt() {
  writestr("%s@platypusOS:# ", CONFIG_USERNAME);
}

void run_command(char input[], char args[]) {
  if (strcmp(input, "version") == 0) {
    version();
  } else if (strcmp(input, "help") == 0) {
    help();
  } else if (strcmp(input, "uname") == 0) {
    uname(args);
  } else if (strcmp(input, "whoami") == 0) {
    whoami();
  } else if (strcmp(input, "cat") == 0) {
    cat(args);
  } else if (strcmp(input, "reboot") == 0) {
    reboot();
  } else if (strcmp(input, "ls") == 0) {
    ls();
  } else if (strcmp(input, "echo") == 0) {
    echo(args);
  } else if (strcmp(input, "playsound") == 0) {
    beep_pcspkr();
  } else if (strcmp(input, "stopsound") == 0) {
    stop_sound_pcspkr();
  } else if (strcmp(input, "panic") == 0) {
    panic("panic command used!");
  } else if (strcmp(input, "hello") == 0) {
    hello();
  } else if (strcmp(input, "mount") == 0) {
    mount();
  } else if (strcmp(input, "\0") == 0) {

  } else {
    writestr("%s: command not found!\n", input);
  }

  for (int i = 0; input[i] != '\0'; i++) {
    input[i] = '\0';
  }
  for (int j = 0; args[j] != '\0'; j++) {
    args[j] = '\0';
  }

  put_prompt();
}

void init_terminal() {
  put_prompt();
}
