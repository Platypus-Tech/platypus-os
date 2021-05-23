#include <vga/vga.h>
#include <gdt.h>

void kernel_init() {
    
     terminal_initialize();

     writestr("Welcome to PlatypusOS!");
     init_gdt();
}
