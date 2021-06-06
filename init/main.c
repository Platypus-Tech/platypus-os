#include <vga/vga.h>
#include <keyboard/keyboard.h>
#include <system/vtconsole.h>
#include <system/terminal.h>
#include <pit/pit.h>
#include <vfs/vfs.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/isr.h>
#include <cpu/irq.h>
#include <kernel/nmi.h>

extern *vtc;
extern void paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y);
extern void cursor_move_callback(vtconsole_t *vtc, vtcursor_t *cur);

void kernel_main() {
    /* Initialize the Terminal */
     terminal_initialize();
    /* Initialize VFS */
     init_vfs();

    /* Load GDT, IDT, ISR, IRQ and PIT */
     init_gdt();
     writestr("[OK] Load GDT\n");
     init_idt();
     writestr("[OK] Load IDT\n");
     init_isr();
     writestr("[OK] Load ISR\n");
     init_irq();
     writestr("[OK] Load IRQ\n");
     nmi_enable();
     writestr("[OK] Enable NMI\n");
     init_timer(100);
     writestr("[OK] Load PIT\n");
    
    /* Load Drivers */
     init_keyboard();
     writestr("[OK] Load Drivers\n");
    
    __asm__ volatile("sti");
    
    vtc = vtconsole(VGA_SCREEN_WIDTH, VGA_SCREEN_HEIGHT, paint_callback, cursor_move_callback);
    
    /* neofetch like result */
    print("\033[1;34mOS: \033[1;37mPlatypusOS x86_32 x86_64 \n");
    print("\033[1;34mKernel: \033[1;37mPlatypus\n");
    print("\033[1;34mVersion: \033[1;37m0.08-dev\n");
    
    settextcolor(COLOR_WHITE, COLOR_BLACK);
    init_terminal();
}
