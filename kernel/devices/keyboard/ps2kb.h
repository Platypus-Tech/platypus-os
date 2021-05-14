/********************************************************************
 * Gonna do OOP for the PS2 Keyboard. Just an idea.                 *
 * (c) DamieFC 2021                                                 *
 ********************************************************************/
#include <stddef.h>
#ifndef PS2_KEYBOARD_H
#ifdef PS2_KEYBOARD_H
#define PS2_KEYBOARD_H /* No, not PS2_KEYBOARD_H overkill at ALL */

#define stdin "keyboard"
struct ps2kb_drvr_platypusos{ /* I like the parenthesis up here :D */
    void init(void); /* initialization */
    void work(void); /* essentially "WORK!! JUST WORK!!" */
}

void work();
void init();

#endif /* PS2_KEYBOARD_H */ /* HAHAHA */
