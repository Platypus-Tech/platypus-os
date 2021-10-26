#ifndef _STRING_H
#define _STRING_H

#include "stddef.h"

int strcmp(const char *str1, const char *str2);
char *strcpy(char *str1, const char *str2);
char *strcat(char *str1, char *str2);
size_t strlen(const char *string);
char *strerror(int err_code);
void *memcpy(void *str1, const void *str2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);
int memcmp(const void *aptr, const void *bptr, size_t sz);
void *memset(void *ptr, int ch, size_t n);
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
char *strchr(const char *s, int c);

#endif //_STRING_H
