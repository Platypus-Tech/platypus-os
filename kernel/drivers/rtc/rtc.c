#include "rtc.h"
#include <cpu/irq.h>
#include <kernel/ports.h>
#include <kernel/rtc_io.h>
#include <stdbool.h>
#include <string.h>

time_t time_global;
bool bcd;

void gettime_rtc(time_t *time) {
  memcpy(time, &time_global, sizeof(time_t));
}

void handler_rtc() {
  if (read_reg(0x0C) & 0x40) {
    if (bcd) {
      time_global.second = bcd_to_bin(read_reg(0x00));
      time_global.minute = bcd_to_bin(read_reg(0x02));
      time_global.hour = bcd_to_bin(read_reg(0x04));
      time_global.month = bcd_to_bin(read_reg(0x08));
      time_global.year = bcd_to_bin(read_reg(0x09));
      time_global.day_of_week = bcd_to_bin(read_reg(0x06));
      time_global.day_of_month = bcd_to_bin(read_reg(0x07));
    } else {
      time_global.second = read_reg(0x00);
      time_global.minute = read_reg(0x02);
      time_global.hour = read_reg(0x04);
      time_global.month = read_reg(0x08);
      time_global.year = read_reg(0x09);
      time_global.day_of_week = read_reg(0x06);
      time_global.day_of_month = read_reg(0x07);
    }
  }
}

void init_rtc() {
  unsigned char status;

  write_reg(0x0A, read_reg(0x0A) | 0x0F);

  status = read_reg(0x0B);
  status |= 0x02;
  status |= 0x10;
  status &= 0x20;
  status &= ~0x20;
  status &= ~0x40;

  bcd = !(status & 0x04);
  write_reg(0x0B, status);
  read_reg(0x0C);
  install_irq_handler(8, handler_rtc);
}
