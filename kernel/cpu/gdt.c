#include "gdt.h"
#include <stdint.h>
#include <string.h>

struct entry_gdt {
  uint16_t low_limit;
  uint16_t low_base;
  uint8_t middle_base;
  uint8_t access;
  uint8_t granularity;
  uint8_t high_base;
} __attribute__((packed));

struct pointer_gdt {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct entry_gdt gdt[3];
struct pointer_gdt gdt_ptr;

void set_gate_gdt(int num, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t gran) {

  /* Set the base address */
  gdt[num].low_base = (base & 0xFFFF);
  gdt[num].middle_base = (base >> 16) & 0xFF;
  gdt[num].high_base = (base >> 24) & 0xFF;

  /* Set the limits */
  gdt[num].low_limit = (limit & 0xFFFF);
  gdt[num].granularity = ((limit >> 16) & 0x0F);

  /* Set the granularity and access flags */
  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

void init_gdt() {
  gdt_ptr.limit = (sizeof(struct entry_gdt) * 6) - 1;
  gdt_ptr.base = (uintptr_t)&gdt;

  set_gate_gdt(0, 0, 0, 0, 0);
  set_gate_gdt(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  set_gate_gdt(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  gdt_load();
}
