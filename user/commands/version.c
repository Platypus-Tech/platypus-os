#include "commands.h"
#include <kernel/vga.h>

void version() {
  writestr("Version 0.11-rc3\n");
}
