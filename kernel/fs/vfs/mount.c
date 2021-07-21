#include <vfs/vfs.h>
#include <vga/vga.h>

/* mount - Print the mounted filesystems */

void mount() {
  if (!vfs_root) {
    writestr("No filesystem mounted.\n");
  }

  writestr("VFS: Mounted on %s\n", vfs_root);
}
