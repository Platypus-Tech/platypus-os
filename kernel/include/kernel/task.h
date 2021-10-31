#ifndef _KERNEL_TASK_H
#define _KERNEL_TASK_H

#include "paging.h"
#include <stdint.h>

typedef struct task {
  const char *name;
  int id;
  uint32_t esp, ebp;
  uint32_t eip;
  page_dir_t *page_directory;
  struct task *next;
} task_t;

void init_tasking();
void task_switch();
void move_to_user_mode();
int fork();
void switch_task();
void move_stack(void *new_stack_start, uint32_t size);
extern void alloc_frame(page_t *, int, int);
extern uint32_t read_eip();
extern void do_task_switch(uint32_t, uint32_t, uint32_t, uint32_t);
int getpid();

#endif //_KERNEL_TASK_H
