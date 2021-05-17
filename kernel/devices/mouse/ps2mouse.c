#include "ps2mouse.h"
#include <log/log.h>
#include <asm/io.h>

void work_mouse() {
    outb(0xD4, 0x64);                    // tell the controller to address the mouse
    outb(0xF3, 0x60);                    // write the mouse command code to the controller's data port
    while(!(inb(0x64) & 1) asm("pause"); // wait until we can read
    ack = inb(0x60);                     // read back acknowledge. This should be 0xFA
    outb(0xD4, 0x64);                    // tell the controller to address the mouse
    outb(100, 0x60);                     // write the parameter to the controller's data port
    while(!(inb(0x64) & 1) asm("pause"); // wait until we can read
    ack = inb(0x60);                     // read back acknowledge. This should be 0xFA
}
          
void init_mouse() {
    int x_mouse_pos;
    int y_mouse_pos;
    int left_btn_pressed = 0;
    int middle_btn_pressed = 0;
    int right_btn_pressed = 0;
    log(INFO, "Mouse Initialized");
    work_mouse();
}

void mouse_driver() {
    init_mouse();
}
