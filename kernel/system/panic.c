#include "panic.h"
#include <vga/vga.h>

void panic(const char *panicmessage) {
    cls();
    writestr("Kernel Panic: %s", panicmessage);
    __asm__ volatile("hlt");
}
