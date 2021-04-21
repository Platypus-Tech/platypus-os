/********************************************************************
 * Keyboard stuff :D                                                *
 * (c) DamieFC                                                      *
 ********************************************************************/
#include <stdio.h>
#include <stddef.h>
#include <log/log.h>
#include "ps2.h"

int ps2_keyboard_driver(){
    struct ps2kb ps2kb
    ps2kb.init init;
    ps2kb.work work;
}

void init(){
    char keymap[59/*?*/] = {
        "esc","`","1","2","3","4","5","6","7","8","9","0","-","+","\b", /* 15 */
        "\t","q","w","e","r","t","y","u","i","o","p","[","]","\\", /* 14 */
        0,"a","s","d","f","g","h","j","k","l",";","'","\n", /* 13 */
        0,"z","x","c","v","b","n","m",",",".","/",0, /* 12 */
        0,0," ",0,0, /* 5 */    /* 15 + 14 + 13 + 12 + 5 is... 59? Then subtract one because it starts at 0, 58? No, 59. AAAA I'll just do 59. */
    }
    log(INFO, "Keyboard initialized!");
}

void work(){
    switch (keymap){
        case 0:
            null
        case 1:
            printf("`");
        case 2:
            printf("1");
        case 3:
            printf("2");
        case 4:
            printf("3");
        case 5:
            printf("4");
        case 6:
            printf("5");
        case 7:
            printf("6");
        default:
            null
    }
}
