#include <stdio.h>
#include <kernel/text.h>
//#include "devices/keyboard/keyboard.h"
#include "devices/mouse/mouse.h"
#include "../libc/include/log.h"

void *kernel_main(void) {
    terminal_initialize();
    log(INFO, "Terminal thing initialized!")
    //ps2kb.init();
    mouse.init();
    log(INFO, "Mouse initialized");
    fptr = fopen("ascii-art.txt","r");
    char c;
    c = fgetc(fptr);
    while (c != EOF){
        printf("%c", c);
        c = fgetc(fptr);
    };
    fclose(fptr);
    writestring("Welcome to Platypus OS!\n");
    writestring("This is still in development, so there isn't anything to do...\n\n\n");
    writestring("Yet.\n");
    writestring("If you want to help, go to https://github.com/Platypus-Tech/new-platypus-os-drafts/ to help\n");
    writestring("...\n");
    writestring("Or to see the source code!");
    //ps2kb.work();
    mouse.work();
    /*return("Chicken butt");*/ /* Eh no chicken butt */
    return("Really serious message :D POO POO PEEPEE"); /* Yeah, REALLY serious */
};
