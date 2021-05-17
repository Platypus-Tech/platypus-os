/************************************************************
 * Kernel functions.                                        *
 * (c) Copyleft DamieFC                                     *
 ************************************************************/

#ifndef _PKERNEL_H
#define _PKERNEL_H

#include <kernel/text.h>
#include <stdio.h>

void print(const char *textthing);
void print(const char *textthing) {
    writestring("%s", textthing);
}

void cls(void);
void cls(void){
    while (terminal_row != 0 && terminal_column != 0){
        printf("\b");
    }
}

#endif //_PKERNEL_H /* My hand hurts :( */
