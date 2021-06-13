#include "vfs.h"
#include <errno.h>
#include <kernel/panic.h>
#include <stdint.h>
#include <vga/vga.h>

/* A simple VFS, based on JamesM's kernel development tutorials */

vfs_node_t *vfs_root = 0;

uint32_t read_vfs(vfs_node_t *node, uint32_t offset, uint32_t size,
                  uint8_t *buf) {
  if (node->read != 0) {
    return node->read(node, offset, size, buf);
  } else {
    /* No such file or directory */
    return -ENOENT;
  }
}

uint32_t write_vfs(vfs_node_t *node, uint32_t offset, uint32_t size,
                   uint8_t *buf) {
  if (node->write != 0) {
    return node->write(node, offset, size, buf);
  } else {
    return -ENOENT;
  }
}

void open_vfs(vfs_node_t *node, uint8_t read, uint8_t write) {
  if (node->open != 0) {
    return node->open(node);
  }
}

void close_vfs(vfs_node_t *node) {
  if (node == vfs_root) {
    panic("Attempted to close vfs_root!\n");
  }

  if (node->close != 0) {
    return node->close(node);
  }
}

struct dirent *readdir_vfs(vfs_node_t *node, uint32_t index) {
  if ((node->flags & 0x7) == VFS_DIR && node->readdir != 0) {
    return node->readdir(node, index);
  } else {
    printm("VFS: Not a directory!\n");
  }
}

vfs_node_t *finddir_vfs(vfs_node_t *node, char *name) {
  if ((node->flags & 0x7) == VFS_DIR && node->readdir != 0) {
    return node->finddir(node, name);
  } else {
    printm("VFS: no such directory\n");
  }
}
