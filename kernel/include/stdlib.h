#ifndef _STDLIB_H
#define _STDLIB_H

#include "stddef.h"

void _Exit(int status);
void exit(int status);
void abort();
int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);

#endif //_STDLIB_H
