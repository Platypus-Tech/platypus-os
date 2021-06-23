#include <string.h>

unsigned short *memsetw(unsigned short *dest, unsigned short val,
                        size_t count) {
  unsigned short *temp = (unsigned short *)dest;

  for (; count != 0; count--) {
    *temp++ = val;
  }

  return dest;
}
