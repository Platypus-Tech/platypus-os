#include <stdio.h>
#include <kernel/text.h>
#include "cpu/gdt.h"
#include "devices/keyboard/keyboard.h"
#include "devices/mouse/ps2mouse.h"
#include "devices/rtc/rtc.h"
#include "../libc/include/log.h"
#include <kernel/weird_numbers.h>
#include "devices/serial/serial.h"

void kernel_main() {
    init_gdt();
    terminal_initialize();
    log(INFO, "Starting System!");
    ps2kb.init();
    log(INFO, "PS/2 Keyboard Initialized");
    init_mouse();
    rtc_init();
    serial_init();
    
    fptr = fopen("ascii-art.txt","r");
    
    char c;
    while (c != EOF) {
        c = fgetc(fptr);
        printf("%c", c);
    };
    
    fclose(fptr);
    writestring("The square root of pi times e is %f", M_1_SQRTPI*M_E);
    writestring("The year is %d", YEAR);
    writestring("Welcome to Platypus OS!\n");
    writestring("This is still in development, so there isn't anything to do...\n...\n...\n");
    writestring("Yet.\n");
    writestring("If you want to help, go to https://github.com/Platypus-Tech/new-platypus-os-drafts/ to help\n");
    writestring("...\n");
    writestring("Or to see the source code!");
};
