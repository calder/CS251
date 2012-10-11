#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Util/Quack.h"


/// All accepted token types
enum
{
    BOOLEAN,
    INTEGER,
    FLOAT,
    STRING,
    SYMBOL,
    OPEN,
    CLOSE
}
typedef TokenType;


/// A single "word" or "punctuation mark" in a program
struct
{
    TokenType type;
    char* value;
}
typedef Token;


/// Return a new Quack of tokens parsed from a chunk of Scheme code
Quack* tokenize (char* input);

/// Display a Token Quack in the form "token:type" with one token per line
void printTokens (Quack* tokens);


#endif