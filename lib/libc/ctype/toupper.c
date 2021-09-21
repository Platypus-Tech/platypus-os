#include <ctype.h>

int toupper(int ch) {
  return islower(ch) ? 'A' + (ch - 'a') : ch;
}
