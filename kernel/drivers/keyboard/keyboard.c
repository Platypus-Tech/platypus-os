#include <cpu/irq.h>
#include <kernel/device.h>
#include <kernel/io.h>
#include <kernel/keyboard.h>
#include <kernel/vga.h>
#include <stdbool.h>
#include <stdint.h>
#include <terminal/terminal.h>

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

  keyboard_key_scancode = inp(KEYBOARD_DATA_PORT);

  if (keyboard_key_scancode & 0x80) {
    // Shift, Ctrl keys to be implemented

  } else {
    uint8_t input = keyboard_layout[keyboard_key_scancode];
    putch(input);
    save_input_buf(input);
  }
}

char buf[40];
int buf_num = 0;
char args[45];
int args_num = 0;
bool is_arg = false;

int save_input_buf(uint8_t input) {
  if (input == '\n') {
    run_command(buf, args);
    buf_num = 0;
    args_num = 0;
    is_arg = false;
    for (int i = 0; buf[i] != '\0'; i++) {
      buf[i] = '\0';
    }
    for (int j = 0; args[j] != '\0'; j++) {
      args[j] = '\0';
    }
  } else if (input == ' ') {
    if (is_arg) {
      args[args_num] = input;
      args_num++;
      return 0;
    }
    is_arg = true;
    return 0;
  } else {
    if (is_arg) {
      args[args_num] = input;
      args_num++;
      return 0;
    }
    buf[buf_num] = input;
    buf_num++;
  }
}

struct device kb_dev = {.name = "keyboard", .id = 1, .path = "/dev/keyboard"};

void init_keyboard() {
  install_irq_handler(1, handler_keyboard);
  add_device(&kb_dev);
}
