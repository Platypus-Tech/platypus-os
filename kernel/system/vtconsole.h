#ifndef _SYSTEM_VTCONSOLE_H
#define _SYSTEM_VTCONSOLE_H

#include <stdbool.h>

#define VTC_DEFAULT_FOREGROUND VTCOLOR_GREY
#define VTC_DEFAULT_BACKGROUND VTCOLOR_BLACK
#define VTC_DEFAULT_ATTR                                                       \
  (vtattr_t) {                                                                 \
    false, VTC_DEFAULT_FOREGROUND, VTC_DEFAULT_BACKGROUND                      \
  }
#define VTC_ANSI_PARSER_STACK_SIZE 8

#define VGA_FRAME_BUFFER 0XB8000

#define VGA_SCREEN_WIDTH 80
#define VGA_SCREEN_HEIGHT 25

#define VGACOLOR_BLACK 0X0
#define VGACOLOR_BLUE 0X1
#define VGACOLOR_GREEN 0X2
#define VGACOLOR_CYAN 0X3
#define VGACOLOR_RED 0X4
#define VGACOLOR_MAGENTA 0X5
#define VGACOLOR_BROWN 0X6
#define VGACOLOR_LIGHT_GRAY 0X7
#define VGACOLOR_GRAY 0X8
#define VGACOLOR_LIGHT_BLUE 0X9
#define VGACOLOR_LIGHT_GREEN 0XA
#define VGACOLOR_LIGHT_CYAN 0XB
#define VGACOLOR_LIGHT_RED 0XC
#define VGACOLOR_LIGHT_MAGENTA 0XD
#define VGACOLOR_LIGHT_YELLOW 0XE
#define VGACOLOR_WHITE 0XF

#define VGA_COLOR(__fg, __bg) (__bg << 4 | __fg)
#define VGA_ENTRY(__c, __fg, __bg)                                             \
  ((((__bg)&0XF) << 4 | ((__fg)&0XF)) << 8 | ((__c)&0XFF))

typedef unsigned int uint;

struct vtconsole;

typedef enum {
  VTCOLOR_BLACK,
  VTCOLOR_RED,
  VTCOLOR_GREEN,
  VTCOLOR_YELLOW,
  VTCOLOR_BLUE,
  VTCOLOR_MAGENTA,
  VTCOLOR_CYAN,
  VTCOLOR_GREY,
} vtcolor_t;

typedef enum {
  VTSTATE_ESC,
  VTSTATE_BRACKET,
  VTSTATE_ATTR,
  VTSTATE_ENDVAL,
} vtansi_parser_state_t;

typedef struct {
  int value;
  bool empty;
} vtansi_arg_t;

typedef struct {
  vtansi_parser_state_t state;
  vtansi_arg_t stack[VTC_ANSI_PARSER_STACK_SIZE];
  int index;
} vtansi_parser_t;

typedef struct {
  bool bright;
  vtcolor_t fg;
  vtcolor_t bg;
} vtattr_t;

typedef struct {
  char c;
  vtattr_t attr;
} vtcell_t;

typedef struct {
  int x;
  int y;
} vtcursor_t;

typedef void (*vtc_paint_handler_t)(struct vtconsole *vtc, vtcell_t *cell,
                                    int x, int y);
typedef void (*vtc_cursor_handler_t)(struct vtconsole *vtc, vtcursor_t *cur);

typedef struct vtconsole {
  int width;
  int height;
  vtattr_t attr;
  vtansi_parser_t ansiparser;
  vtcell_t *buffer;
  vtcursor_t cursor;
  vtc_paint_handler_t on_paint;
  vtc_cursor_handler_t on_move;
} vtconsole_t;

vtconsole_t *vtconsole(int width, int height, vtc_paint_handler_t on_paint,
                       vtc_cursor_handler_t on_move);
void vtconsole_delete(vtconsole_t *c);

void vtconsole_clear(vtconsole_t *vtc, int fromx, int fromy, int tox, int toy);
void vtconsole_scroll(vtconsole_t *vtc, int lines);
void vtconsole_newline(vtconsole_t *vtc);

void vtconsole_putchar(vtconsole_t *vtc, char c);
void vtconsole_write(vtconsole_t *vtc, const char *buffer, uint size);
void print(const char *s);
void vga_cell(unsigned int x, unsigned int y, unsigned short entry);
void vga_cursor(int x, int y);

#endif //_SYSTEM_VTCONSOLE_H
