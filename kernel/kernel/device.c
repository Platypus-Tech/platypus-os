#include <kernel/device.h>
#include <kernel/kheap.h>
#include <kernel/printm.h>
#include <string.h>

#define MAX_DEVICES 10

struct device *devices[MAX_DEVICES];
int next_device_entry = 0;

void add_device(struct device *dev) {
  if (!dev) {
    return;
  }

  devices[next_device_entry] = dev;
  next_device_entry++;
  printm("Registered device %s. id=%d\n", dev->name, dev->id);
}

void init_device() {
  kmalloc(devices);
  memset(devices, 0, MAX_DEVICES * sizeof(struct device));
  printm("Device manager: Intialized\n");
}
