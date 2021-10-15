#include "pit.h"
#include <cpu/irq.h>
#include <kernel/ports.h>

int kernel_timer_ticks = 0;
int timer_freq = 0;

void handler_pit() {
  kernel_timer_ticks++;
}

unsigned read_count_pit() {
  unsigned count = 0;
  irq_disable();
  outp(0x43, 0b0000000);
  count = inp(0x40);
  count |= inp(0x40) << 8;
  irq_enable();
  return count;
}

void sleep_pit(int seconds) {
  int end = kernel_timer_ticks + seconds * timer_freq;
  while (kernel_timer_ticks < end)
    ;
}

void init_pit(int frequency) {
  timer_freq = frequency;
  install_irq_handler(0, handler_pit);
  int divisor = 1193180 / frequency;

  outp(0x43, 0x36);
  outp(0x40, frequency & 0xFF);
  outp(0x40, frequency >> 8);
}
