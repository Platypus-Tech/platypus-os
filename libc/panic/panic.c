#include <panic.h>
#include <log/log.h>

void kpanic(const char panicmessage){
    printf("Kernel panic: %s", panicmessage);
}
