#ifndef _DRIVERS_SERIAL_H
#define _DRIVERS_SERIAL_H

void init_serial();
int received_serial();
char read_serial();
int transmit_empty();
void writechar_serial(char c);
void writestr_serial(const char *str);

#endif //_DRIVERS_SERIAL_H
