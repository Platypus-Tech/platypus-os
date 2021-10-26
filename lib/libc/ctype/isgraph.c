#include <ctype.h>

int isgraph(int ch) {
  return ch >= 0x21 && ch <= 0x7E;
}
