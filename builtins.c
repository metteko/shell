#include "builtins.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static BuiltInCommand commandVector[] = {
    {"exit", exitShell},
    {"pwd", printWorkDir},
    {"cd", changeDir}
};

void exitShell(char** args){
    exit(0);
}

void printWorkDir(char** args){
    char buffer[100];
    getcwd(buffer, 100);
    printf("%s\n", buffer);
}

void changeDir(char** args) {
    if (chdir(args[1]) == 0) {
        printWorkDir(args);
    } else {
        perror("Error in chdir: ");
    }
}

BuiltInCommand* getCommandVector(size_t* count){
    if (count) {
        *count = sizeof(commandVector) / sizeof(commandVector[0]);
    }
    return commandVector;
}


