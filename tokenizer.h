#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <stddef.h>

void addToken(char* token);
void clearTokens();
void addNullToken();
char** getTokens();
size_t getVectorLength();
#endif
