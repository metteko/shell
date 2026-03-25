#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#define VECTOR_LENGTH 10

static char* tokenVector[VECTOR_LENGTH];
static int counter = 0;

void addToken(char* token){
    if (counter < 9){
        size_t tokenLength = strlen(token);
        char* tokenDup = malloc(tokenLength + 1); // Add +1 for the \0 operator
        strcpy(tokenDup, token);
        tokenVector[counter] = tokenDup;
        counter++;
    } else {
        fprintf(stderr, "Token vector is full\n");
    }
}

void clearTokens(){
    for (int i = 0; i < 10; i++){
        free(tokenVector[i]);
        tokenVector[i] = NULL;
    }
    counter = 0;
}

void addNullToken(){
    if (counter == 9){
        tokenVector[9] = NULL;
    } else {
        tokenVector[counter] = NULL;
    }
}

char** getTokens(){
    return tokenVector;
}

size_t getVectorLength() {
    return VECTOR_LENGTH;
}
