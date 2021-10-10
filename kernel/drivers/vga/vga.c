#include "vga.h"
#include <kernel/ports.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

uint16_t *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

void scroll() {
  unsigned blank, temp;

  blank = 0x20 | (attrib << 8);

  if (csr_y >= 25) {
    temp = csr_y - 25 + 1;
    memcpy(textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);
    memsetw(textmemptr + (25 - temp) * 80, blank, 80);
    csr_y = 25 - 1;
  }
}

void move_csr() {
  unsigned temp;

  temp = csr_y * 80 + csr_x;

  outp(0x3D4, 14);
  outp(0x3D5, temp >> 8);
  outp(0x3D4, 15);
  outp(0x3D5, temp);
}

void disable_csr() {
  outp(0x3D4, 0x0A);
  outp(0x3D5, 0x20);
}

uint16_t get_csr_position() {
  uint16_t pos = 0;
  outp(0x3D4, 0x0F);
  pos |= inp(0x3D5);
  outp(0x3D4, 0x0E);
  pos |= ((uint16_t)inp(0x3D5)) << 8;
  return pos;
}

void cls() {
  unsigned blank;

  blank = 0x20 | (attrib << 8);

  for (int i = 0; i < 25; i++) {
    memsetw(textmemptr + i * 80, blank, 80);
  }

  csr_x = 0;
  csr_y = 0;
  move_csr();
}

void putch(uint8_t c) {
  uint16_t *where;
  unsigned att = attrib << 8;

  if (c == 0x08) {
    if (csr_x != 0) {
      csr_x--;
    }
  }

  else if (c == 0x09) {
    csr_x = (csr_x + 8) & ~(8 - 1);
  }

  else if (c == '\r') {
    csr_x = 0;
  }

  else if (c == '\n') {
    csr_x = 0;
    csr_y++;
  }

  else if (c >= ' ') {
    where = textmemptr + (csr_y * 80 + csr_x);
    *where = c | att;
    csr_x++;
  }

  if (csr_x >= 80) {
    csr_x = 0;
    csr_y++;
  }

  scroll();
  move_csr();
}

void writestr(const char *fmt, ...) {
  va_list ap;
  char *p, *sval;
  int ival;
  int xval;

  va_start(ap, fmt);

  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putch(*p);
      continue;
    }

    switch (*++p) {
    case 'd':
      ival = va_arg(ap, int);
      writeint(ival);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++) {
        putch(*sval);
      }
      break;
    case 'x':
      xval = va_arg(ap, int);
      writehex(xval);
      break;
    default:
      putch(*p);
      break;
    }
  }

  va_end(ap);
}

void writeint(uint32_t num) {
  int a = num;
  int i = 0;
  char c[30];

  if (num == 0) {
    writestr("0");
    return;
  }

  while (a > 0) {
    c[i] = '0' + a % 10;
    a /= 10;
    i++;
  }

  c[i] = 0;

  char c2[30];
  c2[i--] = 0;
  int j = 0;

  while (i >= 0) {
    c2[i--] = c[j++];
  }

  writestr(c2);
}

void writehex(uint32_t num) {
  signed int t;

  writestr("0x");

  int no_zeroes = 1;

  for (int i = 28; i > 0; i -= 4) {
    t = (num >> i) & 0xF;
    if (t == 0 && no_zeroes != 0) {
      continue;
    }

    if (t >= 0xA) {
      no_zeroes = 0;
      putch(t - 0xA + 'a');
    } else {
      no_zeroes = 0;
      putch(t + '0');
    }
  }

  t = num & 0xF;
  if (t >= 0xA) {
    putch(t - 0xA + 'a');
  } else {
    putch(t + '0');
  }
}

void settextcolor(uint8_t forecolor, uint8_t backcolor) {
  attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void reset_text_color() {
  settextcolor(WHITE, BLACK);
}

void init_vga() {
  textmemptr = (uint16_t *)0xB8000;
  cls();
}
