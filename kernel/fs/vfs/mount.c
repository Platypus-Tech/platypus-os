#include <vfs/vfs.h>
#include <vga/vga.h>

/* mount - Print the mounted filesystems */

int mount() {
  if (!vfs_root) {
    writestr("No filesystem mounted\n");
    return 1;
  }

  writestr("VFS: Mounted on %s\n", vfs_root);
}
