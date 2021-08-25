#ifndef _KERNEL_RTC_IO_H
#define _KERNEL_RTC_IO_H

#include <kernel/ports.h>

unsigned char read_reg(unsigned char reg) {
  outp(0x70, reg);
  return inp(0x71);
}

void write_reg(unsigned char reg, unsigned char val) {
  outp(0x70, reg);
  outp(0x71, val);
}

unsigned char bcd_to_bin(unsigned char bcd) {
  return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

#endif //_KERNEL_RTC_IO_H
