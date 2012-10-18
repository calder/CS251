#ifndef TOKENS_H
#define TOKENS_H

#include <stdbool.h>


/// All accepted token types
enum
{
    EMPTY_TOKEN,
    BOOLEAN_TOKEN,
    INTEGER_TOKEN,
    FLOAT_TOKEN,
    STRING_TOKEN,
    SYMBOL_TOKEN,
    OPAREN_TOKEN,
    CPAREN_TOKEN
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
        char* stringData;
        char* symbolData;
    };
}
typedef Token;


Token* token_create (TokenType type);

Token* tokenize_bool (char* input, int start, int end);
Token* tokenize_int (char* input, int start, int end);
Token* tokenize_float (char* input, int start, int end);
Token* tokenize_string (char* input, int start, int end);
Token* tokenize_symbol (char* input, int start, int end);
Token* tokenize_paren (char* input, int start, int end);


#endif