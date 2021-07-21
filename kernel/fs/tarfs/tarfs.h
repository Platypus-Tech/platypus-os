#ifndef _FS_TARFS_H
#define _FS_TARFS_H

#include <stdint.h>

struct tarfs_header {
  char filename[100];
  uint8_t mode[8];
  uint8_t uid[8];
  uint8_t gid[8];
  uint8_t size[12];
  uint8_t mtime[12];
  uint8_t checksum[8];
  uint8_t typeflag[1];
};

unsigned int getsize_tarfs(const char *in);
unsigned int parse_tarfs(unsigned int addr);

#endif //_FS_TARFS_H
