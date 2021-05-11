#include "mouse.h"
#include <log/log.h>
#include <asm/io.h>

void mouse_driver(){
    mouse_drvr_platypusos.init_mouse();
    mouse_drvr_platypusos.work_mouse();
}

void init_mouse(){
    int x_mouse_pos;
    int y_mouse_pos;
    int left_butt_pressed = 0; // I did that on purpose xD
    int middle_butt_pressed = 0;
    int right_butt_pressed = 0;
    log(INFO, "Mouse initialized!");
}

void work_mouse(){
    outb(0xD4, 0x64);                    // tell the controller to address the mouse
    outb(0xF3, 0x60);                    // write the mouse command code to the controller's data port
    while(!(inb(0x64) & 1) asm("pause"); // wait until we can read
    ack = inb(0x60);                     // read back acknowledge. This should be 0xFA
    outb(0xD4, 0x64);                    // tell the controller to address the mouse
    outb(100, 0x60);                     // write the parameter to the controller's data port
    while(!(inb(0x64) & 1) asm("pause"); // wait until we can read
    ack = inb(0x60);                     // read back acknowledge. This should be 0xFA
}
