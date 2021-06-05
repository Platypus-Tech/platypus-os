#include "terminal.h"
#include <vga/vga.h>
void putPrompt(void){
    writestr("you@platypusOS:-# ");
}

void checkCommand(void){
    int i;
        for (i=0; i < TOTAL_COMMANDS; i++) {  
            if (input == commands[i]) { 
                run(command); 
            } 
            else { 
                writestr("%s : command not found!", input); 
            }
    }
}
