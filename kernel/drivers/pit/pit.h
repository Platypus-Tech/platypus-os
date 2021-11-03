#ifndef _DRIVERS_PIT_H
#define _DRIVERS_PIT_H

void handler_pit();
void sleep_pit(int ticks);
void init_pit(int hz);

#endif //_DRIVERS_PIT_H
