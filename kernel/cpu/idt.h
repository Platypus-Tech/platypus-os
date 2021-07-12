#ifndef _CPU_IDT_H
#define _CPU_IDT_H

#include <stdint.h>

void init_idt();
extern void idt_load();
void set_gate_idt(int num, uint32_t base, uint16_t sel, uint8_t flags);

#endif //_CPU_IDT_H
