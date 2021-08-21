#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <vga/vga.h>

static char buf[1024];

void printm(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  va_end(args);
}

void show_printm_log() {
  int i;
  for (int i = 0; i < strlen(buf); i++) {
    putch(buf[i]);
    if (buf[i] == '\0') {
      return;
    }
    if (buf[i] == '\n') {
      writestr("\n");
    }
  }
}
