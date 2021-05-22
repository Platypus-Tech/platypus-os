#include <vga.h>

void kernel_init() {
    
     terminal_initialize();

     writestr("Welcome to PlatypusOS!");
}
