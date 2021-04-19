#include <stdio.h>
 
#include <kernel/tty.h>
 
void kernel_main(void) {
	terminal_initialize();
	terminal_writestring("Welcome to Platypus OS\n");
}
