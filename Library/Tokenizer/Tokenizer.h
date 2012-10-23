#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Tokenizer/Tokens.h"
#include "Util/Quack.h"


/// Return a new Quack of tokens parsed from a chunk of Scheme code
Quack* tokenize (const char* input);

/// Display a Token Quack with the format "token:type" with one token per line
void print_tokens (Quack* tokens);


#endif