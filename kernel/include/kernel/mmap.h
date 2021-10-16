#ifndef _KERNEL_MMAP_H
#define _KERNEL_MMAP_H

#include <init/multiboot.h>

void verify_mmap(multiboot_info_t *mboot_info);
void print_mmap(multiboot_info_t *mboot_info);

#endif //_KERNEL_MMAP_H
