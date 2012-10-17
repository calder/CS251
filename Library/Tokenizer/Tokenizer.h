#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Tokenizer/States.h"
#include "Util/Quack.h"


/// Return a new Quack of tokens parsed from a chunk of Scheme code
Quack* tokenize (char* input);

/// Advance the tokenizer one character and return the new DFA state
/// @note Any tokens that get completed are pushed to the back of the Quack.
State* advance_dfa (State* curState, Quack* tokens, char c);

/// Display a Token Quack in the form "token:type" with one token per line
void print_tokens (Quack* tokens);

/// Display a Token Quack in the form "token:type" with one token per line
void print_token (Quack* tokens);


#endif