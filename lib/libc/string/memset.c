#include <string.h>

/* This function is based on the PDCLIB memset function */
void *memset(void *ptr, int ch, size_t n) {

  uint8_t *p = (uint8_t *)ptr;

  while (n--) {
    *p++ = (uint8_t)ch;
  }

  return ptr;
}
