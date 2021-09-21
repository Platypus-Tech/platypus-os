#include <ctype.h>

int isspace(int ch) {
  switch (ch) {
  case '\n':
  case '\r':
  case '\t':
  case '\f':
  case ' ':
  case '\v':
    return 1;
  default:
    return 0;
  }
}
