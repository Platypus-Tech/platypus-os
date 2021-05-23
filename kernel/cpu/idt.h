#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

void init_idt();
extern void idt_load();
void set_gate_idt(int num, uint32_t base, uint16_t sel, uint8_t flags);

#endif //_IDT_H
