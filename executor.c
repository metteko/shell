#include "executor.h"
#include "tokenizer.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>

void processCommand(){
    char** tokenVector = getTokens();
    char* command = tokenVector[0];


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

bool checkBuiltIn(char* command){
    char* builtIns[] = {"exit"};
    int builtInsLength = sizeof(builtIns) / sizeof(builtIns[0]);
    for (int i = 0; i < builtInsLength; i++){
        if (strcmp(builtIns[i], command) == 0){
            return true;
        }
    }
    return false;
}

