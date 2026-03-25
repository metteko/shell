#include "executor.h"
#include "tokenizer.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "builtins.h"
#include <stdio.h>

void processCommand(){
    char** tokenVector = getTokens();
    char* command = tokenVector[0];

    BuiltInCommand builtInCommand = checkBuiltIn(command);
    if (builtInCommand.name != NULL) {
        builtInCommand.func(tokenVector);
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed: ");
    }

    if (pid == 0){
        if(execvp(command, tokenVector) == -1) {
            perror("Exec failed: ");
        }
    } else {
        int status;
        wait(&status);
    }
}

BuiltInCommand checkBuiltIn(char* command){
    size_t count;
    BuiltInCommand* commandVector = getCommandVector(&count);
    for (int i = 0; i < count; i++){
        if (strcmp(commandVector[i].name, command) == 0){
            return commandVector[i];
        }
    }
    BuiltInCommand b = {0}; // Make struct and initialize all members to zero
    return b; 
}
