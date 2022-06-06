#include <kernel/device.h>
#include <kernel/vfs.h>
#include <kernel/vga.h>
#include <string.h>

int ls() {
  if (!vfs_root) {
    writestr("No filesystem mounted\n");
    return 1;
  }

  int i = 0;
  struct vfs_dirent *node = 0;
  while ((node = readdir_vfs(vfs_root, i)) != 0) {
    vfs_node_t *__node = finddir_vfs(vfs_root, node->name);
    if ((__node->flags & 0x7) == VFS_DIR) {
      settextcolor(BLUE, BLACK);
      writestr("%s\n", node->name);
      settextcolor(LIGHT_YELLOW, BLACK);
      print_devices();
    } else {
      settextcolor(LIGHT_YELLOW, BLACK);
      writestr("%s\n", node->name);
    }
    i++;
  }

  reset_text_color();
}
