#include "serial.h"
#include <asm/io.h>
#include <log/log.h>

struct serial_drvr_platypusos serial;

void serial_driver_platypusos(void){
    serial.serial_init();
}
