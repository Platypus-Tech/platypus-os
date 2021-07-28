#include <vfs/vfs.h>
#include <vga/vga.h>

int ls() {
  int i = 0;
  struct vfs_dirent *node = 0;
  while ((node = readdir_vfs(vfs_root, i)) != 0) {
    vfs_node_t *__node = finddir_vfs(vfs_root, node->name);
    if ((__node->flags & 0x7) == VFS_DIR) {
       settextcolor(COLOR_LIGHT_BLUE, COLOR_BLACK);
       writestr(node->name);
       writestr("\n");
    }
    else {
      settextcolor(COLOR_GREEN, COLOR_BLACK);
      writestr(node->name);
      writestr("\n");
    }
    i++;
  }
  
  settextcolor(COLOR_WHITE, COLOR_BLACK);
}
