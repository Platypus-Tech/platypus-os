/*****************************************************************
 * This is partly my code. It has logging functions and stuff.   *
 * The rest is Abb1x's code from Emerald                         *
 * (c) 2021++ DamieFC and (c) 2020 Abb1x                         *
 *****************************************************************/
#include <stddef.h> // idk why, everyone has it :\
#include <stdio.h>
#ifdef LOG_H
/* Why would there be another LOG_H? */
printf("Error, LOG_H defined, for some reason. Overdefining...");
#define LOG_H /* Will this overdefine it or something? */
/*
 INFO is just general info

 WARN is warning level stuff

 ERROR is just error level stuff

 PANIC: kernel panic level stuff that stops everything
*/
enum status
{
    INFO,
    WARNING,
    PANIC,
    ERROR
};

void log(int status, char *format, ...);

#endif /* LOG_H */
