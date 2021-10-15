#include <cpu/irq.h>
#include <kernel/kheap.h>
#include <kernel/paging.h>
#include <kernel/task.h>
#include <stdint.h>

extern volatile task_t *current_task;
extern volatile task_t *ready_queue;
extern uint32_t next_pid;
extern page_dir_t *current_directory;

int fork() {
  irq_disable();

  task_t *parent_task = (task_t *)current_task;
  page_dir_t *directory = clone_directory(current_directory);

  task_t *new_task = (task_t *)kmalloc(sizeof(task_t));

  new_task->id = next_pid++;
  new_task->esp = new_task->ebp = 0;
  new_task->eip = 0;
  new_task->page_directory = directory;
  new_task->next = 0;

  task_t *tmp_task = (task_t *)ready_queue;

  while (tmp_task->next) {
    tmp_task = tmp_task->next;
  }

  tmp_task->next = new_task;

  uint32_t eip = read_eip();

  if (current_task == parent_task) {
    uint32_t esp;
    __asm__ volatile("mov %%esp, %0" : "=r"(esp));
    uint32_t ebp;
    __asm__ volatile("mov %%ebp, %0" : "=r"(ebp));
    new_task->esp = esp;
    new_task->ebp = ebp;
    new_task->eip = eip;

    irq_enable();

    return new_task->id;
  } else {
    return 0;
  }
}
