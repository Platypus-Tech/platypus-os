#include <kernel/log.h>
#include <kernel/printm.h>
#include <pit/pit.h>
#include <vga/vga.h>

extern int kernel_timer_ticks;
const char *last_log;

void warn_log(const char *str) {
  settextcolor(COLOR_RED, COLOR_BLACK);
  writestr("[ %d ] WARN: %s", kernel_timer_ticks, str);
  last_log = str;
  settextcolor(COLOR_WHITE, COLOR_BLACK);
}

void error_log(const char *str) {
  settextcolor(COLOR_RED, COLOR_BLACK);
  writestr("[ %d ] ERROR: %s", kernel_timer_ticks, str);
  last_log = str;
  settextcolor(COLOR_WHITE, COLOR_BLACK);
}

void info_log(const char *str) {
  settextcolor(COLOR_WHITE, COLOR_BLACK);
  writestr("[ %d ] INFO: %s", kernel_timer_ticks, str);
  last_log = str;
}

void show_log() {
  writestr("Last Log: %s", last_log);
}
