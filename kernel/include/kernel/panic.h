#ifndef _KERNEL_PANIC_H
#define _KERNEL_PANIC_H

void panic(const char *panicmessage);
void panic_assert(const char *filename, int line, const char *desc);

#endif //_KERNEL_PANIC_H
