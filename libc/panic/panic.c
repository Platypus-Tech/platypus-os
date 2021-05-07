#include <panic.h>
#include <log/log.h>

void kpanic(const char panicmessage){
    asm(cli);
    printf("Kernel panic: %s", panicmessage);
}
