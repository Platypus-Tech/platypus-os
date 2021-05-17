/************************************************************
 * Kernel functions.                                        *
 * (c) Copyleft DamieFC                                     *
 ************************************************************/
#ifdef PKERNEL_H
#undef PKERNEL_H
#define PKERNEL_H
#else
#ifndef PKERNEL_H
#define PKERNEL_H
#include <kernel/text.h>
#include <stdio.h>

void print(const char *textthing);
void print(const char *textthing){
    writestring("%s", textthing);
}

void cls(void);
void cls(void){
    while (terminal_row != 0 && terminal_column != 0){
        printf("\b");
    }
}

#endif PKERNEL_H /* My hand hurts :( */
