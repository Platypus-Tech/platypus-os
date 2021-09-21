#include <ctype.h>

int tolower(int ch) {
  return isupper(ch) ? 'a' + (ch - 'A') : ch;
}
