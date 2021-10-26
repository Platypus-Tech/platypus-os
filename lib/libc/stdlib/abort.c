#include <stdlib.h>

void abort() {
#ifdef __KERNEL__
  panic("abort()\n");
#endif

  while (1) {
  }
  __builtin_unreachable();
}
