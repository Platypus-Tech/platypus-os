#include "commands.h"
#include <generated/config.h>
#include <vga/vga.h>

void whoami() {
  writestr(CONFIG_USERNAME);
  writestr("\n");
}
