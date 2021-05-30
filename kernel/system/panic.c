#include "panic.h"
#include <vga/vga.h>

void panic(const char *panicmessage) {
    cls();
    settextcolor(COLOR_RED, COLOR_BLACK);
    
    writestr("Kernel Panic: ");
    writestr(panicmessage);
   
   /* Disable the interrupts */
    __asm__ volatile("cli");
   
   /* Halt the CPU */
    __asm__ volatile("hlt");
}
