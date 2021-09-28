#include <ctype.h>

int ispunct(int ch) {
  return isprint(ch) && !isspace(ch) && !isalnum(ch);
}
