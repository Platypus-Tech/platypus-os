#ifndef _DRIVERS_KEYBOARD_H
#define _DRIVERS_KEYBOARD_H

/* PS/2 Keyboard Driver */

#include <stdint.h>

#define DATA_PORT 0x60
#define STATUS_PORT 0x64

/* Initialize the keyboard */
void init_keyboard();

/* Keyboard Handler */
void handler_keyboard();

/* Save Input */
void save_input_buf(uint8_t input);

#endif //_DRIVERS_KEYBOARD_H
