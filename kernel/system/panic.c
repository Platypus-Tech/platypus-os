#include "panic.h"
#include <vga/vga.h>

void panic(const char *panicmessage) {
    cls();
    writestr("Kernel Panic: ");
    writestr(panicmessage);
   
   /* Disable the interrupts */
    __asm__ volatile("cli");
   
   /* Halt the CPU */
    __asm__ volatile("hlt");
}
