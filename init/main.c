#include <vga/vga.h>
#include <keyboard/keyboard.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>

void kernel_main() {
    /* Initialize the Terminal */
     terminal_initialize();
     writestr("Welcome to PlatypusOS!\n");

    /* Load GDT, IDT, ISR and IRQ */
     init_gdt();
     init_idt();
     init_isr();
     init_irq();
    
    /* Load Drivers */
     init_keyboard();
    
    __asm__ volatile("sti");
}
