#include <vga/vga.h>
#include <keyboard/keyboard.h>
#include <system/vtconsole.h>
#include <vfs.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>

extern *vtc;
extern void paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y);
extern void cursor_move_callback(vtconsole_t *vtc, vtcursor_t *cur);

void kernel_main() {
    /* Initialize the Terminal */
     terminal_initialize();
     init_vfs();

    /* Load GDT, IDT, ISR and IRQ */
     init_gdt();
     writestr("[OK] Load GDT\n");
     init_idt();
     writestr("[OK] Load IDT\n");
     init_isr();
     writestr("[OK] Load ISR\n");
     init_irq();
     writestr("[OK] Load IRQ\n");
    
    /* Load Drivers */
     init_keyboard();
     writestr("[OK] Load Drivers\n");
    
    __asm__ volatile("sti");
    
    vtc = vtconsole(VGA_SCREEN_WIDTH, VGA_SCREEN_HEIGHT, paint_callback, cursor_move_callback);
    
    /* sysfetch like result */
    print("\033[1;34mOS: \033[1;37mPlatypusOS x86_32 x86_64 \n");
    print("\033[1;34mKernel: \033[1;37mPlatypus\n");
    print("\033[1;34mVersion: \033[1;37m0.07\n");
    
    settextcolor(COLOR_WHITE, COLOR_BLACK);
    writestr("Hi! There's not much to do yet, but come back later for more stuff!\n");
    writestr("user@kernel: ");
}