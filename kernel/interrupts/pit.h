#ifdef _PIT_H
#undef _PIT_H
#define _PIT_H
#else
#ifndef _PIT_H
#define _PIT_H

void pit_init();
void start_timer(int timer_sec);
void stop_timer();

#endif //_PIT_H
