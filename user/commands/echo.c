#include "commands.h"
#include <string.h>
#include <vga/vga.h>

int echo(char args[]) {
  if (strlen(args) == 0) {
    return 0;
  }
  writestr(args);
  writestr("\n");
}
