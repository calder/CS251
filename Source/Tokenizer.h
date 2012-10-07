#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "stdlib.h"


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


/// An array of parsed Tokens
struct
{
    Token* data;
    int size;
    int capacity;
}
typedef TokenList;


/// Return a new TokenList containing tokens parsed from a chunk of Scheme code
TokenList* createTokenList (char* input);

/// Display a TokenList in the format "token:type" with one token per line
void printTokenList (TokenList* list);


#endif