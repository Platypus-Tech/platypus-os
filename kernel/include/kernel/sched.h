#ifndef _KERNEL_SCHED_H
#define _KERNEL_SCHED_H

#include "thread.h"

typedef struct thread_list {
  thread_t *thread;
  struct thread_list *next;
} thread_list_t;

void thread_is_ready(thread_t *thread);
void thread_not_ready(thread_t *thread);
void schedule();
void init_sched(thread_t *init_thread);

#endif //_KERNEL_SCHED_H
