#include <kernel/kheap.h>
#include <kernel/sched.h>

thread_list_t *ready_queue = 0;
thread_list_t *current_thread = 0;

void thread_is_ready(thread_t *thread) {
  thread_list_t *item = (thread_list_t *)kmalloc(sizeof(thread_list_t *));
  item->thread = thread;
  item->next = 0;

  if (!ready_queue) {
    ready_queue = item;
  } else {
    thread_list_t *iterator = ready_queue;
    while (iterator->next) {
      iterator = iterator->next;
    }
    iterator->next = item;
  }
}

void thread_not_ready(thread_t *thread) {
  thread_list_t *iterator = ready_queue;

  if (iterator->thread == thread) {
    ready_queue = iterator->next;
    kfree(iterator);
    return;
  }

  while (iterator->next) {
    if (iterator->next->thread == thread) {
      thread_list_t *tmp = iterator->next;
      iterator->next = tmp->next;
      kfree(tmp);
    }
    iterator = iterator->next;
  }
}

void schedule() {
  if (!ready_queue) {
    return;
  }

  thread_list_t *iterator = ready_queue;

  while (iterator->next) {
    iterator = iterator->next;
  }

  iterator->next = current_thread;
  current_thread->next = 0;
  thread_list_t *new_thread = ready_queue;
  ready_queue = ready_queue->next;

  switch_thread(new_thread);
}

void init_sched(thread_t *init_thread) {
  current_thread = (thread_list_t *)kmalloc(sizeof(thread_list_t *));
  current_thread->thread = init_thread;
  current_thread->next = 0;
  ready_queue = 0;
}
