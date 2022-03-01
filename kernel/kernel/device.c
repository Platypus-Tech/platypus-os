#include <kernel/device.h>
#include <kernel/kheap.h>
#include <kernel/printm.h>
#include <string.h>

#define MAX_DEVICES 10

struct device *devices[MAX_DEVICES];
int next_device_entry = 0;

void add_device(struct device *dev) {
  if (!dev || next_device_entry == MAX_DEVICES) {
    return;
  }

  devices[next_device_entry] = dev;
  next_device_entry++;
  printm("Registered device %s. id=%d , path=%s\n", dev->name, dev->id,
         dev->path);
}

int get_device_by_id(int id) {
  for (int i = 0; i < next_device_entry; i++) {
    if (devices[i]->id == id) {
      return &devices[i];
    }
  }
}

int remove_device_by_id(int id) {
  for (int i = 0; i < next_device_entry; i++) {
    if (devices[i]->id == id) {
      printm("Removing device %s... ", devices[i]->name);
      devices[i] = 0;
      printm("done\n");
      return 0;
    }
  }
  return 1;
}

int print_devices() {
  if (next_device_entry == 0) {
    return;
  }

  for (int i = 0; i < next_device_entry; i++) {
    writestr("  %s ", devices[i]->name);
  }

  writestr("\n");
  return 0;
}

void init_device_manager() {
  kmalloc(devices);
  printm("[OK] Initialize Device Manager\n");
}
