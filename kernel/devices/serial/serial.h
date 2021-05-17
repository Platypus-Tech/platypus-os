/******************************************************************************
 * Serial driver for Platypus OS                                              *
 * (c) DamieFC 2021                                                           *
 ******************************************************************************/
#ifndef _KERNEL_DEVICES_SERIAL_H
#define _KERNEL_DEVICES_SERIAL_H

void serial_init();
void serial_read();
void serial_driver();
/* char serial_write(char serial_out, port); */

#endif //_KERNEL_DEVICES_SERIAL_H
