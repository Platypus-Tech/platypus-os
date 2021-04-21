/********************************************************************
 * Keyboard stuff :D                                                *
 * (c) DamieFC                                                      *
 ********************************************************************/
#include <stdio.h>
#include <stddef.h>
#include "ps2.h"

int ps2_keyboard_driver(){
    struct ps2kb ps2kb
    ps2kb.init init;
    ps2kb.work work;
}

void init(){
    unsigned char keymap[128] = {
        0,27,"1","2","3","4","5","6","7","8","9","0","-","+","\b",
        "\t","q","w","e","r","t","y","u","i","o","p","[","]","\",
        
    }
}

void work(){
    
}
