#include <kernel/log.h>
#include <pit/pit.h>
#include <printm/printm.h>
#include <vga/vga.h>

extern int kernel_timer_ticks;
struct log *log_info;

void warn_log(const char *str) {
  settextcolor(COLOR_RED, COLOR_BLACK);
  writestr("[ %d ] WARN: %s", kernel_timer_ticks, str);
  log_info->last_log = str;
  settextcolor(COLOR_WHITE, COLOR_BLACK);
}

void error_log(const char *str) {
  settextcolor(COLOR_RED, COLOR_BLACK);
  writestr("[ %d ] ERROR: %s", kernel_timer_ticks, str);
  log_info->last_log = str;
  settextcolor(COLOR_WHITE, COLOR_BLACK);
}

void info_log(const char *str) {
  settextcolor(COLOR_WHITE, COLOR_BLACK);
  writestr("[ %d ] INFO: %s", kernel_timer_ticks, str);
  log_info->last_log = str;
}

void show_log() {
  writestr("Last Log: %s", log_info->last_log);
}
