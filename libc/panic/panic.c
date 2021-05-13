#include <panic.h>
#include <log/log.h>
#include <kernel/pkernel.h>

void kpanic(const char panicmessage){
    cls();
    printf("Kernel panic: %s", panicmessage);
    log(PANIC, "%s", panicmessage);
}
