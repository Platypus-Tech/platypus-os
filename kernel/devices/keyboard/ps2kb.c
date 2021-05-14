/********************************************************************
 * Keyboard stuff :D                                                *
 * (c) DamieFC                                                      *
 ********************************************************************/
#include <stddef.h>
#include <log/log.h>
#include <asm/io.h>
#include "ps2.h"

void ps2_keyboard_driver(){
    struct ps2kb ps2kb
    ps2kb.init init;
    ps2kb.work work;
    ps2kb.init();
    ps2kb.work();
}

void init(){
    char keymap_keys[59/*?*/] = {
        "esc","`","1","2","3","4","5","6","7","8","9","0","-","=","\b", /* 15 */
        "\t","q","w","e","r","t","y","u","i","o","p","[","]","\\", /* 14 */
        0,"a","s","d","f","g","h","j","k","l",";","'","\n", /* 13 */
        0,"z","x","c","v","b","n","m",",",".","/",0, /* 12 */
        0,0," ",0,0, /* 5 */    /* 15 + 14 + 13 + 12 + 5 is... 59? Then subtract one because it starts at 0, 58? No, 59. AAAA I'll just do 59. */
    }
    char keymap_keypad[20] = {
        "NumLock","/","*","-",
        7,8,9,"+",
        4,5,6,"+",
        1,2,3,"\n",
        0,0,".","\n",
    }
    int response = outb(0xF5, 0x60);
    if(response = 0xFA){
        int second_response = outb(0xF2, 0x60);
    }
    log(INFO, "Keyboard initialized!");
}

void work(){
    switch (keymap_keys){
        case 0:
            NULL;
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
        case 8:
            printf("7");
        case 9:
            printf("8");
        case 10:
            printf("9");
        case 11:
            printf("-");
        case 12:
            printf("=");
        case 13:
            printf("\b");
        case 14:
            printf("\t");
        case 15:
            printf("q");
        case 16:
            printf("w");
        case 17:
            printf("e");
        case 18:
            printf("r");
        case 19:
            printf("t");
        case 20:
            printf("y");
        case 21:
            printf("u");
        case 22:
            printf("i");
        case 23:
            printf("o");
        case 24:
            printf("p");
        case 25:
            printf("[");
        case 26:
            printf("]");
        case 27:
            printf("\\");
        case 28:
            NULL;
        case 29:
            printf("a");
        case 30:
            printf("s");
        case 31:
            printf("d");
        case 32:
            printf("f");
        case 33:
            printf("g");
        case 34:
            printf("h");
        case 35:
            printf("j");
        case 36:
            printf("k");
        case 37:
            printf("l");
        case 38:
            printf(";");
        case 39:
            printf("'");
        case 40:
            printf("\n");
        case 41:
            NULL;
        case 42:
            printf("z");
        case 43:
            printf("x");
        case 44:
            printf("c");
        case 45:
            printf("v");
        case 46:
            printf("b");
        case 47:
            printf("n");
        case 48:
            printf("m");
        case 49:
            printf(",");
        case 50:
            printf("/");
        case 51:
            NULL;
        case 52:
            NULL;
        case 53:
            NULL;
        case 54:
            printf(" ");
        case 55:
            NULL;
        case 56:
            NULL;
        default:
            NULL;
    }
    switch(keymap_keypad){
        case 1:
            NULL;
        case 2:
            printf("/");
        case 3:
            printf("*");
        case 4:
            printf("-");
        case 5:
            printf("7");
        case 6:
            printf("8");
        case 7:
            printf("9");
        case 8:
            printf("+");
        case 9:
            printf("4");
        case 10:
            printf("5");
        case 11:
            printf("6");
        case 12:
            printf("+");
        case 13:
            printf("1");
        case 14:
            printf("2");
        case 15:
            printf("3");
        case 16:
            printf("\n");
        case 17:
            printf("0");
        case 18:
            printf("0");
        case 19:
            printf(".");
        case 20:
            printf("\n");
        default: NULL;
    }
}
