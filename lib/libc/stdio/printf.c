#include <kernel/vga.h>
#include <stdarg.h>
#include <stdio.h>

int printf(const char *format, ...) {
  static char buf[1024];
  va_list args;
  va_start(args, format);
  vsprintf(buf, format, args);
  writestr(buf);
  va_end(args);
}
