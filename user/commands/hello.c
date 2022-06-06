#include "commands.h"
#include <kernel/vga.h>

void hello() {
  writestr("Hello to you too?\n");
}
