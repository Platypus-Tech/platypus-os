#include <string.h>

char *strchr(const char *s, int c) {
  while (*s != '\0' && *s != (char)c) {
    s++;
  }

  return (*s != '\0' || c == '\0') ? (char *)s : NULL;
}
