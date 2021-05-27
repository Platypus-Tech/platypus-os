#include <kernel/ports.h>
#include "vga.h"
#include <stdint.h>
#include <stddef.h>
 
void *memcpy(void *dest, const void *src, size_t count) {
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count) {
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *string) {
     size_t length = 0;

     while (string[length]) {
           length++;
     }

     return length;
}

unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;


void scroll() {
    unsigned blank, temp;

    blank = 0x20 | (attrib << 8);

    if(csr_y >= 25) {
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


void cls() {
    unsigned blank;
    int i;

    blank = 0x20 | (attrib << 8);

    for(i = 0; i < 25; i++) {
        memsetw(textmemptr + i * 80, blank, 80);
    }

    csr_x = 0;
    csr_y = 0;
    move_csr();
}


void putch(unsigned char c) {
    unsigned short *where;
    unsigned att = attrib << 8;

    
    if(c == 0x08) {
        if(csr_x != 0) {
            csr_x--;
        }
    }
    
    else if(c == 0x09) {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
   
    else if(c == '\r') {
        csr_x = 0;
    }
    
    else if(c == '\n') {
        csr_x = 0;
        csr_y++;
    }
  
    else if(c >= ' ') {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;
        csr_x++;
    }


    if(csr_x >= 80) {
        csr_x = 0;
        csr_y++;
    }

    scroll();
    move_csr();
}

void writestr(const char *string) {
    int i;

    for (i = 0; i < strlen(string); i++) {
        putch(string[i]);
    }
}


void settextcolor(unsigned char forecolor, unsigned char backcolor) {
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}


void terminal_initialize() {
    textmemptr = (unsigned short *)0xB8000;
    cls();
}