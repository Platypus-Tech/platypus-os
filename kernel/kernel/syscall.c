#include <cpu/irq.h>
#include <cpu/isr.h>
#include <kernel/syscall.h>
#include <stdint.h>
#include <vga/vga.h>

static void syscall_handler(struct registers *regs);

DEFINE_SYSCALL1(writestr, 0, const char *);
DEFINE_SYSCALL1(writehex, 1, const char *);
DEFINE_SYSCALL1(writeint, 2, const char *);
DEFINE_SYSCALL1(putch, 3, const char *);

static void *syscalls[4] = {&writestr, &writehex, &writeint, &putch};

uint32_t num_syscalls = 4;

void init_syscalls() {
  install_irq_handler(0x80, &syscall_handler);
}

void syscall_handler(struct registers *regs) {
  if (regs->eax >= num_syscalls) {
    return;
  }

  void *location = syscalls[regs->eax];
  int ret;

  __asm__ volatile(" \
      push %1; \
      push %2; \
      push %3; \
      push %4; \
      push %5; \
      call *%6; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
    "
                   : "=a"(ret)
                   : "r"(regs->edi), "r"(regs->esi), "r"(regs->edx),
                     "r"(regs->ecx), "r"(regs->ebx), "r"(location));
  regs->eax = ret;
}
