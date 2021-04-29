#include <string.h>
#include <kernel/stdlibio.h>
#include <stddef.h>
#include "../main.h"
*void mset(){
    memset(kernel_main,NULL,1000); // IDK IF THIS WORKS
    printf("Hopefully kernel_main got 1000 bytes of memory.");
}
