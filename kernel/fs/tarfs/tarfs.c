#include "tarfs.h"
#include <kernel/kheap.h>
#include <stdint.h>

struct tarfs_header *headers[32];
int total_files = 0;

void alloc_headers_tarfs() {
  kmalloc(headers);
}

unsigned int getsize_tarfs(const char *in) {
  unsigned int size = 0;
  unsigned int count = 1;
  unsigned int j;

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

  total_files = i;

  return i;
}

int remove_full_path_tarfs() {
  for (int i = 0; i < 32; i++) {
    if (headers[i]->filename[0] == '\0') {
      break;
    }

    headers[i]->filename[0] = ' ';
    headers[i]->filename[1] = ' ';
    headers[i]->filename[2] = ' ';
    headers[i]->filename[3] = ' ';
    headers[i]->filename[4] = ' ';
    headers[i]->filename[5] = ' ';
    headers[i]->filename[6] = ' ';
  }
}

int init_tarfs(uint32_t location) {
  alloc_headers_tarfs();
  parse_tarfs(location);
  remove_full_path_tarfs();
}
