#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "executor.h"

#define BUFFER_SIZE 40
#define SCAN_FORMAT "%39[^\n]"

int main(int argc, char* argv[]){
    char* buffer = malloc(BUFFER_SIZE * sizeof(char));
    while (1){
        printf("mshell>");
        scanf(SCAN_FORMAT, buffer);

        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Clean stdin

        char* token = strtok(buffer, " "); // strtok modifies the buffer, it replaces the 2nd arg with \0
        while (token != NULL){
            addToken(token);
            token = strtok(NULL, " ");
        }
        addNullToken();

        // Execute 
        processCommand();

        clearTokens();
    }
    free(buffer);
    return 0;
}

