#include <generated/config.h>
#include <kernel/printm.h>

#if CONFIG_USERMODE == 'y'
void switch_to_usermode() {
  printm("Switching to usermode...\n");

  __asm__ volatile("  \
     cli; \
     mov $0x23, %ax; \
     mov %ax, %ds; \
     mov %ax, %es; \
     mov %ax, %fs; \
     mov %ax, %gs; \
                   \
     mov %esp, %eax; \
     pushl $0x23; \
     pushl %eax; \
     pushf; \
     pushl $0x1B; \
     push $1f; \
     iret; \
   1: \
     ");
}
#else
void switch_to_usermode() {
  printm("CONFIG_USERMODE is set to n\n");
}
#endif
