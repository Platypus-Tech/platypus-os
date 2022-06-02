#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

/* PS/2 Keyboard Driver */

#include <stdint.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

/* Initialize the keyboard */
void init_keyboard();

/* Keyboard Handler */
void handler_keyboard();

/* Save Input */
int save_input_buf(uint8_t input);

#endif //_KERNEL_KEYBOARD_H
