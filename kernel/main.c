#include <stdio.h>
#include <time.h>
#include <kernel/text.h>
//#include "devices/keyboard/keyboard.h"

void *kernel_main(void) {
    int time_t;
    terminal_initialize();
    //ps2kb.init();
    fptr = fopen("ascii-art.txt","r");
    char c;
    c = fgetc(fptr);
    while (c != EOF){
        printf("%c", c);
        c = fgetc(fptr);
    };
    fclose(fptr);
    writestring("The time is %d", time_t);
    writestring("Welcome to Platypus OS!\n");
    writestring("This is still in development, so there isn't anything to do...\n\n\n");
    writestring("Yet.\n");
    writestring("If you want to help, go to https://github.com/Platypus-Tech/new-platypus-os-drafts/ to help\n");
    writestring("...\n");
    writestring("Or to see the source code!");
    //ps2kb.work();
    /*return("Chicken butt");*/ /* Eh no chicken butt */
    return("Really serious message :D POO POO PEEPEE"); /* Yeah, REALLY serious */
};
