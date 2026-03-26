#include "pipe.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void processPipe(char** left, char** right) {
    int pipefd[2];

    if (pipe(pipefd) == -1){
        perror("Pipe failed: ");
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("First fork in pipe failed: ");
    }

    if (pid1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        char* leftCommand = left[0];
        if (execvp(leftCommand, left) == -1) {
            perror("Exec first command in pipe failed: ");
        }
    }

    pid_t pid2 = fork();
    if (pid2 == -1){
        perror("Second fork in pipe failed: ");
    }

    if (pid2 == 0){
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        char* rightCommand = right[0];
        if (execvp(rightCommand, right) == -1) {
            perror("Exec second command in pipe failed: ");
        }
    }
    // Important to close the main write-ends, otherwise pid2 will not close
    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

}


