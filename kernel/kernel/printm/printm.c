#include <vga/vga.h>
#include <kernel/log.h>
#include "printm.h"

void printm(int log_type, const char *str) {

    if (log_type == INFO) {
       info_log(str);
    }  
    else if (log_type == WARN) {
       warn_log(str);
    }
    else if (log_type == ERROR) {
       error_log(str);
    }
    else if (log_type == MESSAGE) {
       putstr(str, COLOR_WHT, COLOR_BLK);
    }
    else {
       // Do nothing
    } 
}
