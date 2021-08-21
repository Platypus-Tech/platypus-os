#include "pcspkr.h"
#include <kernel/log.h>
#include <kernel/ports.h>
#include <stdint.h>

int is_registered = 0;

void register_snd_driver() {
  if (is_registered == 1) {
    error_log("snd_pcspk_drv is already registered\n");
  } else {
    is_registered = 1;
    info_log("Registered snd_pcspk_drv\n");
  }
}

void play_sound(uint32_t frequency) {
  if (is_registered != 1) {
    // Do nothing
  }

  uint32_t d;
  uint8_t t;

  d = 1193180 / frequency;
  outp(0x43, 0xb6);
  outp(0x42, (uint8_t)(d));
  outp(0x42, (uint8_t)(d >> 8));

  t = inp(0x61);
  if (t != (t | 3)) {
    outp(0x61, t | 3);
  }
}

void stop_sound() {
  uint8_t t = inp(0x61) & 0xFC;

  outp(0x61, t);
}

void beep() {
  play_sound(1000);
}
