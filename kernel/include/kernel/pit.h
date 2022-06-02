#ifndef _KERNEL_PIT_H
#define _KERNEL_PIT_H

void handler_pit();
void sleep_pit(int ticks);
void init_pit(int hz);

#endif //_KERNEL_PIT_H
