#ifndef _KERNEL_THREAD_H
#define _KERNEL_THREAD_H

#include <stdint.h>

typedef struct {
  const char *name;
  uint32_t id;
  uint32_t esp, ebp, ebx, esi, edi, eflags;
} thread_t;

struct thread_list;

extern void __create_thread(int (*)(void *), void *, uint32_t *, thread_t *);
thread_t *create_thread(const char *name, int (*fn)(void *), void *arg,
                        uint32_t *stack);
void switch_thread(struct thread_list *next);
void exit_thread();
thread_t *init_threads();

#endif //_KERNEL_THREAD_H
