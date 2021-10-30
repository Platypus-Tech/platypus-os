#include "commands.h"
#include <vga/vga.h>

void help() {
  writestr(
      "Commands - version reboot help mount ls hello playsound stopsound panic \nuname whoami cat echo\n");
}
