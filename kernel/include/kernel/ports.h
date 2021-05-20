#ifndef _KERNEL_PORTS_H
#define _KERNEL_PORTS_H

#include <stdint.h>

uint8_t inp(unsigned short port);
void outp(unsigned short port, unsigned char data);

#endif //_KERNEL_PORTS_H
