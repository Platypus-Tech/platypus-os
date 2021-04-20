#ifndef _STDIO_H
#define _STDIO_H 1
 
#include <sys/cdefs.h>
 
#define EOF (-1)
 
#ifdef __cplusplus
extern "C" {
#endif
 
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
size_t  _EXFUN(fread, (void *, size_t _size, size_t _n, FILE *)); /* fread() */
extern FILE *fopen (const char *__restrict __filename,
                    const char *__restrict __modes) __wur; /* fopen() */
extern int fclose (FILE *__stream); /* fclose() */

#ifdef __cplusplus
}
#endif
 
#endif
