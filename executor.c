#include "executor.h"
#include "tokenizer.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "builtins.h"
#include <stdio.h>
#include <stdbool.h>
#include "pipe.h"

void processCommand(){
    char** tokenVector = getTokens();
    char* command = tokenVector[0];

    char* left[10];
    char* right[10];
    bool hasPipe = checkPipe(tokenVector, left, right);
    if (hasPipe) {
        processPipe(left, right);
        return;
    }

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


// Check for pipe character
bool checkPipe(char** tokenVector, char** left, char** right) {
    for (int i = 0; i < getVectorLength(); i++) {
        char* pipeChar = "|";
        if (strcmp(tokenVector[i], pipeChar) == 0) {
            // Left
            for (int j = 0; j < i; j++) {
                left[j] = tokenVector[j];
            }
            // Adding NULL for exec
            left[i] = NULL;
            
            // Right
            int counter;
            for (int k = 0; k < (getVectorLength() - (i+1)); k++) {
                right[k] = tokenVector[(i+1)+k];
                counter = k;
            }
            right[counter + 1] = NULL;
            return true;
        }
    }
    return false;
}
