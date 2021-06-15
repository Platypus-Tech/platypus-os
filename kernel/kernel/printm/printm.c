#include "printm.h"
#include <kernel/log.h>
#include <vga/vga.h>

void printm(int log_type, const char *str) {

  if (log_type == INFO) {
    info_log(str);
  } else if (log_type == WARN) {
    warn_log(str);
  } else if (log_type == ERROR) {
    error_log(str);
  } else if (log_type == MESSAGE) {
    writestr(str);
  } else {
    // Do nothing
  }
}
