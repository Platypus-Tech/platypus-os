#include <ctype.h>

int isalpha(int ch) {
  return islower(ch) || isupper(ch);
}
