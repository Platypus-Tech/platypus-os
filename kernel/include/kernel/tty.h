#ifndef _KERNEL_TEXT_H
#define _KERNEL_TEXT_H

#include <stddef.h>

void terminal_initialize(void);
void putchar(char c);
void write(const char* data, size_t size);
void writestring(const char* data);

#endif
