#ifndef _DRIVERS_SOUND_H
#define _DRIVERS_SOUND_H

#include <stdint.h>

void beep();
void play_sound(uint32_t frequency);
void stop_sound();
void register_snd_driver();

#endif //_DRIVERS_SOUND_H
