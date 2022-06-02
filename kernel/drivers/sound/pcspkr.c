#include <kernel/io.h>
#include <kernel/pcspkr.h>

int is_registered = 0;

void play_sound_pcspkr(uint32_t frequency) {
  if (is_registered != 1) {
    return;
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

void stop_sound_pcspkr() {
  uint8_t t = inp(0x61) & 0xFC;

  outp(0x61, t);
}

void beep_pcspkr() {
  play_sound_pcspkr(1000);
}

int init_pcspkr() {
  if (is_registered == 1) {
    return -1;
  } else {
    is_registered = 1;
    return 0;
  }
}
