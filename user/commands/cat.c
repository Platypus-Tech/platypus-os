#include "commands.h"
#include <string.h>
#include <vfs/vfs.h>
#include <vga/vga.h>

int cat(char args[]) {
  if (strlen(args) == 0) {
    return 0;
  }

  int i = 0;
  struct vfs_dirent *node = 0;
  while ((node = readdir_vfs(vfs_root, i)) != 0) {
    vfs_node_t *fsnode = finddir_vfs(vfs_root, node->name);

    if ((fsnode->flags & 0x7) == VFS_DIR && strcmp(fsnode->name, args) == 0) {
      writestr("cat: %s: is a directory\n", args);
      return 0;
    } else {
      if (strcmp(fsnode->name, args) == 0) {
        char buf[256];
        uint32_t sz = read_vfs(fsnode, 0, 256, buf);
        for (int j = 0; j < sz; j++) {
          putch(buf[j]);
        }
        return 0;
      }
    }
    i++;
  }

  writestr("cat: %s: no such file or directory\n", args);
  return 0;
}
