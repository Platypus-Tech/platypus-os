/********************************************************************
 * Gonna do OOP for the keyboard. Just an idea.                     *
 * (c) DamieFC 2021                                                 *
 ********************************************************************/
#include <stddef.h>
#ifndef KEYBOARD_H
#ifdef KEYBOARD_H
#define KEYBOARD_H /* No, not KEYBOARD_H overkill at ALL */

struct keyboard{ /* I like the parenthesis up here :D */
    void (*init)(void); /* initialization */
    void (*work)(void); /* essentially "WORK!! JUST WORK!!" */
}

void work();
void init();
