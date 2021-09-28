#ifndef _CTYPE_H
#define _CTYPE_H

#define MIN_DIGIT 0
#define MAX_DIGIT 9

int isalpha(int ch);
int isalnum(int ch);
int isblank(int ch);
int isdigit(int ch);
int islower(int ch);
int isupper(int ch);
int isspace(int ch);
int toupper(int ch);
int tolower(int ch);
int ispunct(int ch);
int isxdigit(int ch);
int isprint(int ch);
int iscntrl(int ch);
int isgraph(int ch);

#endif //_CTYPE_H
