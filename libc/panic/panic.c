#include <panic.h>
#include <log/log.h>

void kpanic(void){
    printf("PANIC!!!!\n");
    printf("Something happened :(\n");
    printf("No idea what, actually. Maybe the computer went on a bathroom break. Maybe you miswired something. Maybe the Grim Reaper killed the computer. Maybe you messed up the QEMU image.\n");
    printf("No way of knowing right now.\n");
    printf("Help update this code so have better information, including error codes, and maybe so this can automatically heal!\n");
}
