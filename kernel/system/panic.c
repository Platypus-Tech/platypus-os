#include "panic.h"
#include "../drivers/vga/vga.h"

void panic(const char panicmessage) {
    cls();
    writestr("PANIC: %s", panicmessage);
    writestr("That's all we know");
}
