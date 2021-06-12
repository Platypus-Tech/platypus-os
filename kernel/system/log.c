#include <kernel/log.h>
#include <vga/vga.h>

struct log *log_info;

void warn_log(const char *str) {
  putstr("WARN: ", COLOR_RED, COLOR_BLK);
  putstr(str, COLOR_RED, COLOR_BLK);
  log_info->last_log = str;
}

void error_log(const char *str) {
  putstr("ERROR: ", COLOR_RED, COLOR_BLK);
  putstr(str, COLOR_RED, COLOR_BLK);
  log_info->last_log = str;
}

void info_log(const char *str) {
  putstr("INFO: ", COLOR_WHT, COLOR_BLK);
  printm(str);
  log_info->last_log = str;
}

void show_log() {
  printm("Last Log: ");
  printm(log_info->last_log);
}
