#include "floppy.h"
#include <kernel/ports.h>
#include <kernel/printm.h>
#include <stdint.h>

static const char *drive_types[7] = {"no drive",          "360 KB 5.25 Drive",
                                     "1.2 MB 5.25 Drive", "720 KB 3.5 Drive",
                                     "1.44 MB 3.5 Drive", "2.88 MB 3.5 Drive",
                                     "unknown drive"};

void detect_drives_floppy() {
  outp(0x70, 0x10);
  uint8_t drives = inp(0x71);
  printm("Floppy drive 0: %s, 1: %s\n", drive_types[drives >> 4],
         drive_types[drives & 0xF]);
}
