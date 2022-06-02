#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

void init_serial();
int received_serial();
char read_serial();
int transmit_empty();
void writechar_serial(char c);
void writestr_serial(const char *str);

#endif //_KERNEL_SERIAL_H
