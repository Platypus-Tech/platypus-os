#ifndef _KERNEL_PCSPKR_H
#define _KERNEL_PCSPKR_H

#include <stdint.h>

void beep_pcspkr();
void play_sound_pcspkr(uint32_t frequency);
void stop_sound_pcspkr();
int init_pcspkr();

#endif //_KERNEL_PCSPKR_H
