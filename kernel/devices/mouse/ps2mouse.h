/**************************************************************
 * IDK computer mouse driver                                  *
 * (c) Copyleft 2021 DamieFC                                  *
 **************************************************************/
#ifndef _PS2MOUSE_H
#define _PS2MOUSE_H // Must be sure :D

struct mouse_driver {
  int x_mouse_pos;
  int y_mouse_pos;
  int left_btn_pressed;
  int middle_btn_pressed;
  int right_btn_pressed;
}

void init_mouse();
void work_mouse();

#endif _PS2MOUSE_H
