#include <vga/vga.h>
#include <string.h>
#include "terminal.h"

void put_prompt() {
    writestr("you@platypusOS:# ");
}

void run_command(char input[]) {
    if (strcmp(input, "version")==0) {
        writestr("Version 0.08-dev\n");
    }
    else if (strcmp(input, "help")==0) {
        writestr("Commands - version help uname\n");
    }
    else if (strcmp(input, "uname")==0) {
        writestr("PlatypusOS\n");
    }
    else if (strcmp(input, "\0") == 0) {
    
    }
    else {
        writestr("%s : command not found!\n", input);
    }

    for (int i = 0; input[i] != '\0'; i++) {
      input[i] = '\0';
    }

    put_prompt();
}

void init_terminal() {
    put_prompt();
}
