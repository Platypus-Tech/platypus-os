#include <ctype.h>

int isprint(int ch) {
  return ch >= 0x20 && ch <= 0x7E;
}
