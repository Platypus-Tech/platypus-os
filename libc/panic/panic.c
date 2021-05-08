#include <panic.h>
#include <log/log.h>

void kpanic(const char panicmessage){
    asm("cls");
    printf("Kernel panic: %s", panicmessage);
}
