#include <string.h>

char *strcpy(char *str1, const char *str2) {
  char *rc = str1;

  while ((*str1++ = *str2++)) {
  }

  return rc;
}
