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

void print(const char *textthing);
void print(const char *textthing){
    writestring("%s", textthing);
}

#endif PKERNEL_H /* My hand hurts :( */
