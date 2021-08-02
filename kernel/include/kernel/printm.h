#ifndef _KERNEL_PRINTM_H
#define _KERNEL_PRINTM_H

#define INFO "KERN_INFO"
#define WARN "KERN_WARN"
#define ERROR "KERN_ERROR"
#define DEBUG "KERN_DEBUG"
#define MESSAGE "KERN_MESSAGE"
#define PANIC "KERN_PANIC"

void printm(const char *log_type, const char *str);

#endif //_KERNEL_PRINTM_H
