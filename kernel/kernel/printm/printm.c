#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <vga/vga.h>

#define PRINTM_BUF_SIZE 1024

static char buf[PRINTM_BUF_SIZE];

void printm(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  va_end(args);
  show_printm_log();
}

void show_printm_log() {
  int i;
  for (int i = 0; i < strlen(buf); i++) {
    putch(buf[i]);
    if (buf[i] == '\0') {
      return;
    }
  }
}
