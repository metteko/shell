#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "executor.h"

#define BUFFER_SIZE 40
#define SCAN_FORMAT "%39[^\n]"

int main(int argc, char* argv[]){
    printf("Type help to start\n");
    char* buffer = malloc(BUFFER_SIZE * sizeof(char));
    while (1){
        printf("mshell>");
        int matches = scanf(SCAN_FORMAT, buffer);

        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Clean stdin
        
        // Checking empty i.e. no input
        if (matches != 0) {
            char* token = strtok(buffer, " "); // strtok modifies the buffer, it replaces the 2nd arg with \0
            while (token != NULL){
                addToken(token);
                token = strtok(NULL, " ");
            }
            // Last token should be NULL for execvp
            addNullToken();

            processCommand();

            clearTokens();
            memset(buffer, 0, sizeof(buffer));
        }
    }
    free(buffer);
    return 0;
}
