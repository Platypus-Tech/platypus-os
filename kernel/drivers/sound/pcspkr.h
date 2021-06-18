#ifndef _DRIVERS_PCSPKR_H
#define _DRIVERS_PCSPKR_H

#include <stdint.h>

void beep();
void play_sound(uint32_t frequency);
void stop_sound();
void register_snd_driver();

#endif //_DRIVERS_PCSPKR_H
