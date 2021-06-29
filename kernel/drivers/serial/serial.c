#include "serial.h"
#include <kernel/log.h>
#include <kernel/ports.h>

#define SERIAL_COM1 0x3f8

int received_serial() {
  return inp(SERIAL_COM1 + 5) & 1;
}

char read_serial() {
  while (received_serial() == 0)
    ;

  return inp(SERIAL_COM1);
}

int transmit_empty() {
  return inp(SERIAL_COM1 + 5) & 0x20;
}

void writechar_serial(char c) {
  while (transmit_empty() == 0)
    ;

  outp(SERIAL_COM1, c);
}

void writestr_serial(const char *str) {
  while (*str) {
    writechar_serial(*str++);
  }
}

void init_serial() {
  outp(SERIAL_COM1 + 1, 0x00);
  outp(SERIAL_COM1 + 3, 0x80);
  outp(SERIAL_COM1 + 0, 0x03);
  outp(SERIAL_COM1 + 1, 0x00);
  outp(SERIAL_COM1 + 3, 0x03);
  outp(SERIAL_COM1 + 2, 0xC7);
  outp(SERIAL_COM1 + 4, 0x0B);
  outp(SERIAL_COM1 + 4, 0x1E);
  outp(SERIAL_COM1 + 0, 0xAE);

  if (inp(SERIAL_COM1 + 0) != 0xAE) {
    error_log("Faulty serial device");
    return;
  }

  outp(SERIAL_COM1 + 4, 0x0F);
}
