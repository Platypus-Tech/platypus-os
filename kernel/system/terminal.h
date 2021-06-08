/**********************************************************
 * The terminal ported from KinuxOS with new code         *
 * Ported code (c) DamieFC 2021 original code (c)         *
 * kushagra765 under the Unlicense                        *
 **********************************************************
 */

#ifndef _SYSTEM_TERMINAL_H
#define _SYSTEM_TERMINAL_H

void put_prompt();
void run_command(char input[]);
void init_terminal();
void reboot();

#endif //_SYSTEM_TERMINAL_H
