#ifndef _FS_TARFS_H
#define _FS_TARFS_H

struct tarfs_header {
  char filename[100];
  char mode[8];
  char uid[8];
  char gid[8];
  char size[12];
  char mtime[12];
  char checksum[8];
  char typeflag[1];
};

unsigned int getsize_tarfs(const char *in);
unsigned int parse_tarfs(unsigned int addr);
void alloc_headers_tarfs();
int init_tarfs();

#endif //_FS_TARFS_H
