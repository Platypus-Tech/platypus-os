#ifndef _DRIVERS_KEYBOARD_H
#define _DRIVERS_KEYBOARD_H

/* PS/2 Keyboard Driver */

#define DATA_PORT 0x60
#define STATUS_PORT 0x64

/* Initialize the keyboard */
void init_keyboard();

/* Keyboard Handler */
void handler_keyboard();

#endif //_DRIVERS_KEYBOARD_H
