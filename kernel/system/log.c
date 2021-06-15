#include <kernel/log.h>
#include <printm/printm.h>
#include <vga/vga.h>

struct log *log_info;

void warn_log(const char *str) {
  settextcolor(COLOR_RED, COLOR_BLACK);
  writestr("WARN: %s", str);
  log_info->last_log = str;
}

void error_log(const char *str) {
  settextcolor(COLOR_RED, COLOR_BLACK);
  writestr("ERROR: %s", str);
  log_info->last_log = str;
}

void info_log(const char *str) {
  settextcolor(COLOR_WHITE, COLOR_BLACK);
  writestr("INFO: %s", str);
  log_info->last_log = str;
}

void show_log() {
  writestr("Last Log: %s", log_info->last_log);
}
