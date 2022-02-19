#include <cpu/irq.h>
#include <cpu/isr.h>
#include <kernel/elf.h>
#include <kernel/panic.h>
#include <kernel/printm.h>
#include <kernel/task.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <vga/vga.h>

bool assert_panic_in_progress;
extern elf_t kernel_elf;
extern task_t *current_task;

void panic_remove_newline(char str[]) {
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '\n') {
      str[i] = '\0';
    }
  }
}

void panic_assert(const char *filename, int line, const char *desc) {
  assert_panic_in_progress = true;
  irq_disable();

  printm("Assertion failed (%s) : %s:%d\n", desc, filename, line);
  panic("Assertion failed\n");
}

void print_stack_trace() {
  uint32_t *ebp, *eip;
  __asm__ volatile("mov %%ebp, %0" : "=r"(ebp));

  printm("Stack Trace: \n");

  while (ebp) {
    eip = ebp + 1;
    printm("           [0x%x] %s\n", *eip,
           lookup_symbol_elf(*eip, &kernel_elf));
    ebp = (uint32_t *)*ebp;
  }
}

void panic(char panicmessage[]) {
  struct registers *regs;

  if (!assert_panic_in_progress) {
    irq_disable();
  }

  panic_remove_newline(panicmessage);
  settextcolor(LIGHT_GRAY, BLACK);

  /* This is based on Linux */
  printm("Kernel Panic: not syncing, %s\n", panicmessage);
  printm("PID: %d Comm: %s\n", current_task->id, current_task->name);

  printm("Registers:  ");
  printm("GS: 0x%x FS: 0x%x ES: 0x%x DS: 0x%x CS: 0x%x SS: 0x%x\n", regs->gs,
         regs->fs, regs->es, regs->ds, regs->cs, regs->ss);
  printm(
      "EDI: 0x%x ESI: 0x%x EBP: 0x%x ESP: 0x%x EBX: 0x%x EDX: 0x%x ECX: 0x%x EAX: 0x%x\n",
      regs->edi, regs->esi, regs->ebp, regs->esp, regs->ebx, regs->edx,
      regs->ecx, regs->eax);
  print_stack_trace();
  printm("---[end Kernel Panic: not syncing, %s ]---", panicmessage);

  /* Halt the CPU */
  __asm__ volatile("hlt");
}
