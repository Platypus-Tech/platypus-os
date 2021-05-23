#include <vga/vga.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>

void kernel_init() {
    /* Initialize the Terminal */
     terminal_initialize();
     writestr("Welcome to PlatypusOS!");

    /* Load GDT, IDT, ISR and IRQ*/
     init_gdt();
     init_idt();
     init_isr();
     init_irq();
}
