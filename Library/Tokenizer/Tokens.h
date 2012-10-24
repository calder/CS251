#ifndef TOKENS_H
#define TOKENS_H

#include <stdbool.h>


/// All accepted token types
enum
{
    EMPTY_TOKEN,
    END_TOKEN,
    BOOLEAN_TOKEN,
    FLOAT_TOKEN,
    INTEGER_TOKEN,
    PAREN_TOKEN,
    STRING_TOKEN,
    SYMBOL_TOKEN,
}
typedef TokenType;


/// A single "word" or "punctuation mark" in a program
struct
{
    TokenType type;
    union
    {
        bool boolData;
        int intData;
        float floatData;
        char parenData;
        char* stringData;
        char* symbolData;
    };
}
typedef Token;


/// Malloc and return a new Token
Token* token_create (TokenType type);

/// Free all memory associated with a token
/// @note stringData and symbolData are both assumed to be dynamically allocated
/// memory and will be freed.
void token_free (Token* token);

/// Print a token's value followed by a space
void token_print (Token* token);

/// Print a token as "type: value"
void token_print_debug (Token* token);


#endif