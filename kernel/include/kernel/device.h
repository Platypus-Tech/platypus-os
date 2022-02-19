#ifndef _KERNEL_DEVICE_H
#define _KERNEL_DEVICE_H

#include <stdint.h>

struct device {
  const char *name;
  uint32_t id;
};

void add_device(struct device *dev);
int get_device_by_id(int id);
int remove_device_by_id(int id);
void init_device_manager();

#endif //_KERNEL_DEVICE_H
