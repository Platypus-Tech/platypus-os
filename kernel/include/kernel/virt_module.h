#ifndef _KERNEL_VIRT_MODULE_H
#define _KERNEL_VIRT_MODULE_H

struct virt_module {
  char module_name[51];
  char module_license[5];
  int is_loaded;
};

int add_module(char name[], char license[]);
int remove_module(char name[]);
int check_module_license(char name[]);

#endif //_KERNEL_VIRT_MODULE_H
