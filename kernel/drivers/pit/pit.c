#include <cpu/irq.h>
#include <kernel/io.h>
#include <kernel/pit.h>
#include <kernel/task.h>

int pit_ticks = 0;
int pit_hz = 0;

void handler_pit() {
  pit_ticks++;
  switch_task();
}

void phase_pit(int hz) {
  int divisor = 1193180 / hz;
  outp(0x43, 0x36);
  outp(0x40, divisor & 0xFF);
  outp(0x40, divisor >> 8);
}

void sleep_pit(int ticks) {
  unsigned long eticks;
  eticks = pit_ticks + ticks * pit_hz;
  while (pit_ticks < eticks)
    ;
}

void init_pit(int hz) {
  install_irq_handler(0, handler_pit);
  phase_pit(hz);
  pit_hz = hz;
}
