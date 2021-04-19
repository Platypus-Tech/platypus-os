#include <stdio.h>
 
#include <kernel/tty.h>
 
void kernel_main(void) {
	terminal_initialize();
	terminal_writestring("Welcome to Platypus OS!\n");
	terminal_writestring("This is still in development, so there isn't anything to do...\n\n\n");
	terminal_writestring("Yet.\n");
	terminal_writestring("If you want to help, go to https://github.com/Platypus-Tech/new-platypus-os-drafts/ to help\n\n");
	terminal_writestring("Or to see the source code!");
}
