/**************************************************************
 * IDK computer mouse driver                                  *
 * (c) Copyleft 2021 DamieFC                                  *
 **************************************************************/
#ifdef _PS2MOUSE_H
#undef _PS2MOUSE_H
#define _PS2MOUSE_H
#else
#ifndef _PS2MOUSE_H
#define _PS2MOUSE_H // Must be sure :D

struct mouse_drvr_platypusos {
    void init_mouse();
    void work_mouse();
}

#endif _PS2MOUSE_H
