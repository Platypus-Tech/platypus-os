#include <kernel/vga.h>
#include <stdarg.h>
#include <stdio.h>

#define PRINTM_BUF_SIZE 1024

static char buf[PRINTM_BUF_SIZE];

void printm(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  writestr("[kernel] ");
  writestr(buf);
  va_end(args);
}
