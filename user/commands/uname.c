#include "commands.h"
#include <generated/config.h>
#include <string.h>

int uname(char args[]) {
  if (strcmp(args, "-s") == 0) {
    writestr("Platypus\n");
    return 0;
  } else if (strcmp(args, "-o") == 0) {
    writestr("PlatypusOS\n");
    return 0;
  } else if (strcmp(args, "-m") == 0) {
    writestr(CONFIG_ARCH);
    writestr("\n");
    return 0;
  } else {
    writestr("PlatypusOS\n");
    return 0;
  }
}
