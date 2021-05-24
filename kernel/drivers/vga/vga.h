#ifndef _DRIVERS_VGA_H
#define _DRIVERS_VGA_H

void scroll();
void move_csr();
void cls();
void putch(unsigned char c);
void writestr(unsigned char *text);
void settextcolor(unsigned char forecolor, unsigned char backcolor);
void terminal_initialize();

#endif //_DRIVERS_VGA_H
