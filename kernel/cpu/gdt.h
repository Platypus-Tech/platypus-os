#ifndef _CPU_GDT_H
#define _CPU_GDT_H

#include <stdint.h>

void init_gdt();
extern void gdt_load();
void set_gate_gdt(int num, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t gran);

#endif //_CPU_GDT_H
