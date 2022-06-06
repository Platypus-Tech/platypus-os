#include "commands.h"
#include <kernel/vga.h>
#include <string.h>

int echo(char args[]) {
  if (strlen(args) == 0) {
    return 0;
  }
  writestr(args);
  writestr("\n");
}
