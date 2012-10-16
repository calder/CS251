#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Util/Quack.h"
#include "Util/Set.h"


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

/// Advance the tokenizer one character and return the new NFA state
/// @note Any tokens that get completed are pushed to the back of the Quack.
/// @note The calling function takes ownership of the returned NFA state Set.
Set* advance_nfa (Set* nfa, Quack* tokens, char c);

/// Display a Token Quack in the form "token:type" with one token per line
void print_tokens (Quack* tokens);

/// Display a Token Quack in the form "token:type" with one token per line
void print_token (Quack* tokens);


#endif