#ifndef _STDLIB_H
#define _STDLIB_H

#include "stddef.h"

void exit(int status);
void abort(void);
void _exit(int status);
char *getenv(const char *name);

#endif //_STDLIB_H
