#ifndef _KERNEL_PORTS_H
#define _KERNEL_PORTS_H

#include <stdint.h>

uint8_t port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);

#endif //_KERNEL_PORTS_H
