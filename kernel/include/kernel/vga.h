#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H

#include <stdint.h>

#define BLACK 0x0
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GRAY 0x7
#define GRAY 0x8
#define BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_MAGENTA 0xD
#define LIGHT_YELLOW 0xE
#define WHITE 0xF

void scroll();
void move_csr();
void disable_csr();
uint16_t get_csr_position();
void cls();
void putch(uint8_t c);
void writestr(const char *fmt, ...);
void writeint(uint32_t num);
void writehex(uint32_t num);
void settextcolor(uint8_t forecolor, uint8_t backcolor);
void reset_text_color();
void init_vga();

#endif //_KERNEL_VGA_H
