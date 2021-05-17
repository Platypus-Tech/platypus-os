/************************************************************
 * PC speaker header file                                   *
 * (c) 2021 DamieFC                                         *
 ************************************************************/
#ifdef PCSPKR_H
#undef PCSPKR_H
#define PCSPKR_H
#else
#ifndef PCSPKR_H
#define PCSPKR_H

struct pcspkr_drvr_platypusos{
    void pcspkr_init();
    void beep();
    void mute();
}
