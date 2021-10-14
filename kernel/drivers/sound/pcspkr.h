#ifndef _DRIVERS_SOUND_PCSPKR_H
#define _DRIVERS_SOUND_PCSPKR_H

#include <stdint.h>

void beep_pcspkr();
void play_sound_pcspkr(uint32_t frequency);
void stop_sound_pcspkr();
int init_pcspkr();

#endif //_DRIVERS_SOUND_PCSPKR_H
