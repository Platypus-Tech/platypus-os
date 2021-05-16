#ifdef PIT_H
#undef PIT_H
#define PIT_H
#else
#ifndef PIT_H
#define PIT_H

void pit_init(void);
void start_timer(int timer_sec);
void stop_timer(void);

#endif PIT_H
