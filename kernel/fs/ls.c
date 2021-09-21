#include <tarfs/tarfs.h>
#include <vga/vga.h>

extern struct tarfs_header *headers[32];

int ls() {
  for (int i = 0; i < 32; i++) {
    if (headers[i]->filename == '\0') {
      break;
    }

    writestr(headers[i]->filename);
    writestr("\n");
  }

  return 0;
}
