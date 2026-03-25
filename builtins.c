#include "builtins.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "tokenizer.h"

static BuiltInCommand commandVector[] = {
    {"exit", exitShell},
    {"pwd", printWorkDir},
    {"cd", changeDir},
    {"echo", echo},
    {"help", help}    
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

void echo(char** args){
    for (int i = 1; i < getVectorLength(); i++){
        if (args[i] != NULL) {
            printf("%s ", args[i]);
        }
    }
    printf("\n");
    fflush(stdout);
}

void help(char** args){
    printf("Welcome to Metteko's custom shell!\n\n");
    printf("This shell consist of two types of commands: built-ins and external binaries.\n");
    printf("External binaries are executed through the fork()/exec() pattern\n");
    printf("Built-in commands are implemented by myself, check them out:\n\n");
    printf("exit\npwd\ncd\necho\nhelp\n\n");
}

BuiltInCommand* getCommandVector(size_t* count){
    if (count) {
        *count = sizeof(commandVector) / sizeof(commandVector[0]);
    }
    return commandVector;
}


