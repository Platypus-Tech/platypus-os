#ifdef PIT_H
#undef PIT_H
#define PIT_H
#else
#ifndef PIT_H
#define PIT_H

void start_timer(int timer_sec);
void start_infinite_timer(void);
void stop_timer(void);

#endif PIT_H
