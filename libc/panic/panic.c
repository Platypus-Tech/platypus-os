#include <panic.h>
#include <log/log.h>
#include <stdlib.h>

void kpanic(const char panicmessage){
    system("clear");
    printf("Kernel panic: %s", panicmessage);
}
