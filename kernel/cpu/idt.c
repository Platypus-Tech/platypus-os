#include "idt.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

struct entry_idt {
  uint16_t lo_base;
  uint16_t sel;
  uint8_t always0;
  uint8_t flags;
  uint16_t hi_base;
} __attribute__((packed));

struct pointer_idt {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct entry_idt idt[256];
struct pointer_idt idt_ptr;

void set_gate_idt(int num, uint32_t base, uint16_t sel, uint8_t flags) {

  idt[num].lo_base = base & 0xFFFF;
  idt[num].hi_base = (base >> 16) & 0xFFFF;
  idt[num].sel = sel;
  idt[num].always0 = 0;
  idt[num].flags = flags | 0x60;
}

void init_idt() {

  idt_ptr.limit = (sizeof(struct entry_idt) * 256) - 1;
  idt_ptr.base = (uintptr_t)&idt;
  memset(&idt, 0, sizeof(struct entry_idt) * 256);

  idt_load();
}
