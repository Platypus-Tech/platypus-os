#include "keyboard.h"
#include <irq.h>
#include <kernel/ports.h>
#include <stdint.h>
#include <terminal/terminal.h>
#include <vga/vga.h>

uint8_t keyboard_layout[128] = {
    0,   27,   '1',  '2', '3',  '4', '5', '6', '7', '8', '9', '0', '-',
    '=', '\b', '\t', 'q', 'w',  'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    '[', ']',  '\n', 0,   'a',  's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    ';', '\'', '`',  0,   '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',',
    '.', '/',  0,    '*', 0,    ' ', 0,   0,   0,   0,   0,   0,   0,
    0,   0,    0,    0,   0,    0,   0,   0,   0,   '-', 0,   0,   0,
    '+', 0,    0,    0,   0,    0,   0,   0,   0,   0,   0,   0,
};

void handler_keyboard() {
  uint8_t keyboard_key_scancode;

  keyboard_key_scancode = inp(DATA_PORT);

  if (keyboard_key_scancode & 0x80) {
    // Shift, Ctrl keys to be implemented

  } else {
    uint8_t input = keyboard_layout[keyboard_key_scancode];
    putch(input, COLOR_WHT, COLOR_BLK);
    save_input_buf(input);
  }
}

uint8_t buf[40];
int num = 0;

void save_input_buf(uint8_t input) {
  if (input == '\n') {
    run_command(buf);
    num = 0;
  } else {
    buf[num] = input;
    num++;
  }
}

void init_keyboard() {
  install_irq_handler(1, handler_keyboard);
}
