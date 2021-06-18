#ifndef _DRIVERS_VGA_H
#define _DRIVERS_VGA_H

#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_LIGHT_GREY 7
#define COLOR_DARK_GREY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MANGENTA 13
#define COLOR_LIGHT_BROWN 14
#define COLOR_WHITE 15

void scroll();
void move_csr();
void cls();
void putch(unsigned char c);
void writestr(const char *fmt, ...);
void writeint(int num);
void settextcolor(unsigned char forecolor, unsigned char backcolor);
void init_vga();

#endif //_DRIVERS_VGA_H
