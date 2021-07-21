#include <vfs/vfs.h>
#include <vga/vga.h>

void ls() {
  int i = 0;
  struct vfs_dirent *node = 0;
  while ((node = readdir_vfs(vfs_root, i)) != 0) {
    writestr(node->name);
    writestr("\n");
    i++;
  }
}
