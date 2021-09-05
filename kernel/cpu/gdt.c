#include "gdt.h"
#include "tss.h"
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

struct entry_gdt gdt[6];
struct pointer_gdt gdt_ptr;
struct tss_entry __tss_entry;

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

void write_tss(int32_t num, uint16_t ss0, uint32_t esp0) {
  uint32_t base = (uint32_t)&__tss_entry;
  uint32_t limit = base + sizeof(__tss_entry);

  set_gate_gdt(num, base, limit, 0xE9, 0x00);
  memset(&__tss_entry, 0, sizeof(__tss_entry));
  __tss_entry.ss0 = ss0;
  __tss_entry.esp0 = esp0;
  __tss_entry.cs = 0x0b;
  __tss_entry.ss = __tss_entry.ds = __tss_entry.es = __tss_entry.fs =
      __tss_entry.gs = 0x13;
}

void set_kernel_stack(uint32_t stack) {
  __tss_entry.esp0 = stack;
}

void init_gdt() {
  gdt_ptr.limit = (sizeof(struct entry_gdt) * 6) - 1;
  gdt_ptr.base = (uintptr_t)&gdt;

  set_gate_gdt(0, 0, 0, 0, 0);
  set_gate_gdt(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  set_gate_gdt(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  set_gate_gdt(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  set_gate_gdt(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
  write_tss(5, 0x10, 0x0);

  gdt_load();
  flush_tss();
}
