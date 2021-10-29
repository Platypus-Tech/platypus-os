#include <kernel/kheap.h>
#include <kernel/printm.h>
#include <kernel/sched.h>
#include <kernel/thread.h>
#include <string.h>

thread_t *curr_thread;
uint32_t next_tid = 0;

thread_t *create_thread(const char *name, int (*fn)(void *), void *arg,
                        uint32_t *stack) {
  thread_t *thread = kmalloc(sizeof(thread_t));
  memset(thread, 0, sizeof(thread_t));
  thread->name = name;
  thread->id = next_tid++;

  *--stack = (uint32_t)arg;
  *--stack = (uint32_t)&exit_thread;
  *--stack = (uint32_t)fn;

  thread->esp = (uint32_t)stack;
  thread->ebp = 0;
  thread->eflags = 0x200;
  thread_is_ready(thread);

  return thread;
}

void exit_thread() {
  register uint32_t val __asm__("eax");

  printm("Thread exited with value 0x%x\n", val);
}

thread_t *init_threads() {
  thread_t *thread = kmalloc(sizeof(thread_t));
  thread->name = "init";
  thread->id = next_tid++;
  curr_thread = thread;
  return thread;
}
