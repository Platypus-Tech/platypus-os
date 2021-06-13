#ifndef _KERNEL_PRINTM_H
#define _KERNEL_PRINTM_H

#define INFO 0
#define WARN 1
#define ERROR 2
#define MESSAGE 4

void printm(int log_type, const char *str);

#endif //_KERNEL_PRINTM_H