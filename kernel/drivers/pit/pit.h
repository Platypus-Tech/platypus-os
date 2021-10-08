#ifndef _DRIVERS_PIT_H
#define _DRIVERS_PIT_H

void handler_pit();
unsigned read_count_pit();
void sleep_pit(int seconds);
void init_pit(int frequency);

#endif //_DRIVERS_PIT_H
