/**********************************************************
 * The terminal ported from KinuxOS with new code         *
 * Ported code (c) DamieFC 2021 original code (c)         *
 * kushagra765 under the Unlicense                        *
 **********************************************************/

#ifndef _TERMINAL_H
#define _TERMINAL_H

void putPrompt(void);
void checkCmd(void);
void init_terminal(void);

char *commands[] = {
    "version", "help", "uname";
}
#endif _TERMINAL_H
