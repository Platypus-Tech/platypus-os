#ifndef _DRIVERS_PCSPKR_PCSPKR_H
#define _DRIVERS_PCSPKR_PCSPKR_H

#include <stddef.h>
#include <stddint.h> // Not sure if I need it

void pcspkr_init(void);
void beep(size_t frequency);
