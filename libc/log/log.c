/**************************************************
 * Logging stuff                                  *
 * Again, only partly my code                     * 
 * (c) 2021++ DamieFC and (c) 2020 Abb1x          *
 **************************************************/

#include "log.h"

char *current_module = "";
void log(int status, char *format, ...)
{
    char *string;
    switch (status)
    {
    case INFO:
        string = "[INFO:] ";
        break;
    case WARNING:
        string = "[WARNING:] ";
        break;
    case ERROR:
        string = "[ERROR:] ";
        break;
    case PANIC:
        string = "[!!!PANIC!!!:] ";
        break;
    default:
        string = " string";
    };
    printf(string, current_module, " ");
};
