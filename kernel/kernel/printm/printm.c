#include <kernel/log.h>
#include <kernel/panic.h>
#include <kernel/printm.h>
#include <serial/serial.h>
#include <string.h>
#include <vga/vga.h>

void printm(const char *log_type, const char *str) {
  if (strcmp(log_type, INFO) == 0) {
    info_log(str);
  } else if (strcmp(log_type, WARN) == 0) {
    warn_log(str);
  } else if (strcmp(log_type, ERROR) == 0) {
    error_log(str);
  } else if (strcmp(log_type, DEBUG) == 0) {
    writestr_serial(str);
  } else if (strcmp(log_type, MESSAGE) == 0) {
    writestr(str);
  } else if (strcmp(log_type, PANIC) == 0) {
    panic(str);
  } else {
    writestr("ERROR: Cannot print %s, logtype = %s\n", str, log_type);
  }
}
