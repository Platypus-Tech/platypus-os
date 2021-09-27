#include <cpu/irq.h>
#include <cpu/isr.h>
#include <kernel/panic.h>
#include <stdint.h>
#include <string.h>
#include <terminal/terminal.h>
#include <vga/vga.h>

extern const char *cmd;

void panic_remove_newline(char str[]) {
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '\n') {
      str[i] = '\0';
    }
  }
}

void panic_assert(const char *filename, int line, const char *desc) {
  irq_disable();

  writestr("Assertion failed (%s): %s:%d\n", desc, filename, line);
  panic("Assertion failed\n");
}

void panic(char panicmessage[]) {
  struct registers *regs;

  irq_disable();
  panic_remove_newline(panicmessage);
  settextcolor(LIGHT_GRAY, BLACK);

  /* This is based on Linux */
  writestr("Kernel Panic: not syncing, %s\n", panicmessage);
  writestr("Command: %s\n", cmd);

  writestr("Registers:  ");
  writestr("GS: %x FS: %x ES: %x DS: %x CS: %x SS: %x\n", regs->gs, regs->fs,
           regs->es, regs->ds, regs->cs, regs->ss);
  writestr("EDI: %x ESI: %x EBP: %x ESP: %x EBX: %x EDX: %x ECX: %x EAX: %x\n",
           regs->edi, regs->esi, regs->ebp, regs->esp, regs->ebx, regs->edx,
           regs->ecx, regs->eax);
  writestr("---[end Kernel Panic: not syncing, %s ]---", panicmessage);

  /* Halt the CPU */
  __asm__ volatile("hlt");
}
