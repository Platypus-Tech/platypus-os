#include "commands.h"
#include <generated/config.h>
#include <kernel/vga.h>

void whoami() {
  writestr("%s\n", CONFIG_USERNAME);
}
