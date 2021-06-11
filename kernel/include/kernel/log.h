#ifndef _KERNEL_LOG_H
#define _KERNEL_LOG_H

struct log {
  const char *last_log;
};

void warn_log(const char *str);
void error_log(const char *str);
void info_log(const char *str);
void show_log();

#endif //_LOG_H
