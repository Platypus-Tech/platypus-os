#ifndef _KERNEL_TEXT_H
#define _KERNEL_TEXT_H

#include <stddef.h>

static size_t terminal_row;
static size_t terminal_column;

void terminal_initialize(void);
void putchar(char c);
void write(const char* data, size_t size);
void writestring(const char* data);

#endif
