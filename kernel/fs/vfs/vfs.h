#ifndef _VFS_H
#define _VFS_H

#include <stdint.h>

#define VFS_FILE 0x01
#define VFS_DIR 0x02
#define VFS_CHARDEVICE 0x03
#define VFS_BLOCKDEVICE 0x04
#define VFS_PIPE 0x05
#define VFS_SYMLINK 0x06
#define VFS_MOUNTPOINT 0x08

struct vfs_dirent {
  char name[128];
  uint32_t inode_num;
};

typedef uint32_t (*read_type_t)(struct vfs_node *, uint32_t, uint32_t,
                                uint8_t *);
typedef uint32_t (*write_type_t)(struct vfs_node *, uint32_t, uint32_t,
                                 uint8_t *);
typedef void (*open_type_t)(struct vfs_node *);
typedef void (*close_type_t)(struct vfs_node *);
typedef struct vfs_dirent *(*readdir_type_t)(struct vfs_node *, uint32_t);
typedef struct vfs_node *(*finddir_type_t)(struct vfs_node *, char *name);

typedef struct vfs_node {
  char name[128];
  uint32_t mask;
  uint32_t uid;
  uint32_t gid;
  uint32_t flags;
  uint32_t inode;
  uint32_t length;
  uint32_t impl;
  read_type_t read;
  write_type_t write;
  open_type_t open;
  close_type_t close;
  readdir_type_t readdir;
  finddir_type_t finddir;
  struct fs_node *ptr;
} vfs_node_t;

extern vfs_node_t *vfs_root;

uint32_t read_vfs(vfs_node_t *node, uint32_t offset, uint32_t size,
                  uint8_t *buf);
uint32_t write_vfs(vfs_node_t *node, uint32_t offset, uint32_t size,
                   uint8_t *buf);
void open_vfs(vfs_node_t *node, uint8_t read, uint8_t write);
void close_vfs(vfs_node_t *node);
struct vfs_dirent *readdir_vfs(vfs_node_t *node, uint32_t index);
vfs_node_t *finddir_vfs(vfs_node_t *node, char *name);

#endif //_VFS_H
