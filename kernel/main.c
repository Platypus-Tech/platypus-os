#include <stdio.h>
#include <kernel/text.h>
//#include "devices/keyboard/keyboard.h"
#include "devices/mouse/ps2mouse.h"
#include "devices/rtc/rtc.h"
#include "../libc/include/log.h"
#include <kernel/weird_numbers.h>

void *kernel_main(void) {
    struct mouse_drvr_platypusos mouse;
    struct rtc_drvr_platypusos rtc;
    
    terminal_initialize();
    log(INFO, "Terminal thing initialized!");
    //ps2kb.init();
    mouse.init();
    rtc.init();
    log(INFO, "Mouse initialized");
    fptr = fopen("ascii-art.txt","r");
    char c;
    c = fgetc(fptr);
    while (c != EOF){
        printf("%c", c);
        c = fgetc(fptr);
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
    //ps2kb.work();
    mouse.work();
    log(INFO, "Mouse working!");
    rtc.work();
    log(INFO, "RTC working!");
    /*return("Chicken butt");*/ /* Eh no chicken butt */
    return("Really serious message :D POO POO PEE PEE"); /* Yeah, REALLY serious */
};
