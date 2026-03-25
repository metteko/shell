#ifndef BUILTINS_H
#define BUILTINS_H
#include <stddef.h>

typedef struct {
    char* name;
    void (*func)(char** args); // Function pointer, argument is an array of char*
} BuiltInCommand;

void exitShell(char** args);

void printWorkDir(char** args);
void changeDir(char** args);

BuiltInCommand* getCommandVector(size_t* count);

#endif
