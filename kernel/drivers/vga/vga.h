#ifndef _DRIVERS_VGA_H
#define _DRIVERS_VGA_H

#include <stdint.h>
#include <stddef.h>

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

void init_terminal();
void setcolor(uint8_t color);
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
static inline uint16_t vga_entry(uint8_t c, uint8_t color);
void putentry(char c, uint8_t color, size_t x, size_t y);
void putchar(char c);
void write(const char *string, size_t size);
void writestr(const char *string);

#endif //_DRIVERS_VGA_H
