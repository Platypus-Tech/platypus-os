/**************************************************************
 * IDK computer mouse driver                                  *
 * (c) Copyleft 2021 DamieFC                                  *
 **************************************************************/
#ifdef PS2MOUSE_H
#undef PS2MOUSE_H
#define PS2MOUSE_H
#else
#ifndef PS2MOUSE_H
#define PS2MOUSE_H // Must be sure :D

struct mouse_drvr_platypusos{
    void init_mouse();
    void work_mouse();
}

#endif PS2MOUSE_H
