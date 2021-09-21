#ifndef _DRIVERS_PIT_H
#define _DRIVERS_PIT_H

void handler_pit();
unsigned read_pit_count();
void init_pit(int frequency);

#endif //_DRIVERS_PIT_H
