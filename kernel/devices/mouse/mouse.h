/**************************************************************
 * IDK computer mouse driver                                  *
 * (c) Copyleft 2021 DamieFC                                  *
 **************************************************************/
#ifdef MOUSE_H
#undef MOUSE_H
#define MOUSE_H
#else
#ifndef MOUSE_H
#define MOUSE_H // Must be sure :D

struct mouse_drvr_platypusos{
    void init_mouse();
    void work_mouse();
}
