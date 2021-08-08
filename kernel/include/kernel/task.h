#ifndef _KERNEL_TASK_H
#define _KERNEL_TASK_H

#include "paging.h"
#include <stdint.h>

typedef struct task {
  int id;
  uint32_t esp, ebp;
  uint32_t eip;
  page_dir_t *page_directory;
  struct task *next;
} task_t;

void init_tasking();
void task_switch();
int fork();
void move_stack(void *new_stack_start, uint32_t size);
int getpid();

#endif //_KERNEL_TASK_H
