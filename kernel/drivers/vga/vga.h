#ifndef _DRIVERS_VGA_H
#define _DRIVERS_VGA_H

void init_vga();
void clear_screen();
void cursor_move();
void screen_scroll();
void set_color(unsigned char forecolor, unsigned char backcolor);
void putc(unsigned char c);
void writestring(unsigned char *str);

#endif //_DRIVERS_VGA_H
