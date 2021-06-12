#ifndef _VGA_H
#define _VGA_H

/* drivers/vga/vga.h
 * Author - @jaychandra6
 */

// define basic constants
#define VGA_START 0xb8000 // VGA start address
#define VGA_WIDTH 80      // these are max coloumns in VGA
#define VGA_HEIGHT 25     // these are max rows in VGA
#define VGA_EXTENT 80 * 25

//---------------------------------------------------
// defining available colors
#define COLOR_BLK 0  // Black
#define COLOR_BLU 1  // Blue
#define COLOR_GRN 2  // Green
#define COLOR_CYN 3  // Cyan
#define COLOR_RED 4  // Red
#define COLOR_PRP 5  // Purple
#define COLOR_BRN 6  // Brown
#define COLOR_GRY 7  // Gray
#define COLOR_DGY 8  // Dark Gray
#define COLOR_LBU 9  // Light Blue
#define COLOR_LGR 10 // Light Green
#define COLOR_LCY 11 // Light Cyan
#define COLOR_LRD 12 // Light Red
#define COLOR_LPP 13 // Light Purple
#define COLOR_YEL 14 // Yellow
#define COLOR_WHT 15 // White

//---------------------------------------------------

// I/O ports which map the screen cursor position can be queried
// from port 0x3d4 with value 14 to request the cursor position high byte
// and we also query the same port with value 15 in the low byte
// when this port is queried, the result is saved in 0x3d5

// cursor ports:
// command port = 0x3d4 query the cursor position here
// data port = 0x3d5 read from here
#define CURSOR_PORT_COMMAND (unsigned short)0x3d4
#define CURSOR_PORT_DATA (unsigned short)0x3d5

//---------------------------------------------------
// define a single character struct with close packing
typedef struct __attribute__((packed)) {
  char character;
  char style;
} vga_char;

// apply foreground and background colors to the character
unsigned char vga_color(const unsigned char fg_color,
                        const unsigned char bg_color);

// clear the window or screen with a color
void clearwin(const unsigned char fg_color, const unsigned char bg_color);

// print a character to the screen
void putch(const char character, const unsigned char fg_color,
             const unsigned char bg_color);

// print a string to the screen
void printm(const char *str);
void putstr(const char *string, const unsigned char fg_color,
            const unsigned char bg_color);

// get the cursor position
unsigned short get_cursor_pos();

// show or hide cursor functions
void show_cursor();
void hide_cursor();

// set the cursor position
void advance_cursor();
void set_cursor_pos(unsigned char x, unsigned char y);

// scroll line
void scroll_line();

#endif //_VGA_H
