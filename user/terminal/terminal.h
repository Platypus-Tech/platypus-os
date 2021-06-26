/**********************************************************
 * The terminal ported from KinuxOS with new code         *
 * Ported code (c) DamieFC 2021 original code (c)         *
 * kushagra765 under the Unlicense                        *
 **********************************************************
 */

#ifndef _USER_TERMINAL_H
#define _USER_TERMINAL_H

void put_prompt();
void run_command(char input[]);
void init_terminal();

#endif //_USER_TERMINAL_H
