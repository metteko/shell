#include "builtins.h"
#include <stdlib.h>

static BuiltInCommand commandVector[] = {
    {"exit", exitShell}
};

void exitShell(char** args){
    exit(0);
}

BuiltInCommand* getCommandVector(size_t* count){
    if (count) {
        *count = sizeof(commandVector) / sizeof(commandVector[0]);
    }
    return commandVector;
}


