#ifndef _INITRD_H
#define _INITRD_H

#include <stdint.h>
#include <vfs/vfs.h>

typedef struct {
  uint32_t nfiles;
} initrd_header_t;

typedef struct {
  uint8_t magic;
  char name[64];
  uint32_t offset;
  uint32_t length;
} initrd_file_header_t;

vfs_node_t *init_initrd(uint32_t location);

#endif //_INITRD_H
