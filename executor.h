#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "builtins.h"
#include <stdbool.h>

void processCommand();
BuiltInCommand checkBuiltIn(char* command); 
bool checkPipe(char** tokenVector, char** left, char** right);

#endif
