#include "mouse.h"

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
}
