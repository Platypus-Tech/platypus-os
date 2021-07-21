#include "tarfs.h"
#include <stdint.h>

struct tarfs_header *headers[32];

unsigned int getsize_tarfs(const char *in) {
  unsigned int size = 0;
  unsigned int j;
  unsigned int count = 1;

  for (j = 11; j > 0; j--, count *= 8) {
    size += ((in[j - 1] - '0') * count);
  }

  return size;
}

unsigned int parse_tarfs(unsigned int addr) {
  unsigned int i;

  for (i = 0;; i++) {
    struct tarfs_header *header = (struct tarfs_header *)addr;

    if (header->filename[0] == '\0') {
      break;
    }

    unsigned int size = getsize_tarfs(header->size);
    headers[i] = header;
    addr += ((size / 512) + 1) * 512;

    if (size % 512) {
      addr += 512;
    }
  }

  return i;
}
