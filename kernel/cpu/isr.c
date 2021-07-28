#include "isr.h"
#include "idt.h"
#include <kernel/printm.h>
#include <stdint.h>

void init_isr() {

  set_gate_idt(0, (uintptr_t)isr0, 0x08, 0x8E);
  set_gate_idt(1, (uintptr_t)isr1, 0x08, 0x8E);
  set_gate_idt(2, (uintptr_t)isr2, 0x08, 0x8E);
  set_gate_idt(3, (uintptr_t)isr3, 0x08, 0x8E);
  set_gate_idt(4, (uintptr_t)isr4, 0x08, 0x8E);
  set_gate_idt(5, (uintptr_t)isr5, 0x08, 0x8E);
  set_gate_idt(6, (uintptr_t)isr6, 0x08, 0x8E);
  set_gate_idt(7, (uintptr_t)isr7, 0x08, 0x8E);
  set_gate_idt(8, (uintptr_t)isr8, 0x08, 0x8E);
  set_gate_idt(9, (uintptr_t)isr9, 0x08, 0x8E);
  set_gate_idt(10, (uintptr_t)isr10, 0x08, 0x8E);
  set_gate_idt(11, (uintptr_t)isr11, 0x08, 0x8E);
  set_gate_idt(12, (uintptr_t)isr12, 0x08, 0x8E);
  set_gate_idt(13, (uintptr_t)isr13, 0x08, 0x8E);
  set_gate_idt(14, (uintptr_t)isr14, 0x08, 0x8E);
  set_gate_idt(15, (uintptr_t)isr15, 0x08, 0x8E);
  set_gate_idt(16, (uintptr_t)isr16, 0x08, 0x8E);
  set_gate_idt(17, (uintptr_t)isr17, 0x08, 0x8E);
  set_gate_idt(18, (uintptr_t)isr18, 0x08, 0x8E);
  set_gate_idt(19, (uintptr_t)isr19, 0x08, 0x8E);
  set_gate_idt(20, (uintptr_t)isr20, 0x08, 0x8E);
  set_gate_idt(21, (uintptr_t)isr21, 0x08, 0x8E);
  set_gate_idt(22, (uintptr_t)isr22, 0x08, 0x8E);
  set_gate_idt(23, (uintptr_t)isr23, 0x08, 0x8E);
  set_gate_idt(24, (uintptr_t)isr24, 0x08, 0x8E);
  set_gate_idt(25, (uintptr_t)isr25, 0x08, 0x8E);
  set_gate_idt(26, (uintptr_t)isr26, 0x08, 0x8E);
  set_gate_idt(27, (uintptr_t)isr27, 0x08, 0x8E);
  set_gate_idt(28, (uintptr_t)isr28, 0x08, 0x8E);
  set_gate_idt(29, (uintptr_t)isr29, 0x08, 0x8E);
  set_gate_idt(30, (uintptr_t)isr30, 0x08, 0x8E);
  set_gate_idt(31, (uintptr_t)isr31, 0x08, 0x8E);
}

const char *exceptions[] = {"Division by zero",
                            "Debug",
                            "Non Maskable Interrupt",
                            "Breakpoint exception",
                            "Into Detected Overflow",
                            "Out of Bounds exception",
                            "Invalid Opcode exception",
                            "No Coprocessor exception",

                            "Double Fault exception",
                            "Coprocessor Segment Overrun",
                            "Bad TSS exception",
                            "Segment Not Present",
                            "Stack Fault exception",
                            "General Protection Fault",
                            "Page Fault exception",
                            "Unknown Interrupt exception",

                            "Coprocessor Fault exception",
                            "Alignment Check exception",
                            "Machine Check exception",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",

                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved"};

void handler_isr(struct registers *regs) {

  if (regs->int_no <= 31) {
    printm(2, exceptions[regs->int_no]);
    for (;;)
      ;
  }
}
