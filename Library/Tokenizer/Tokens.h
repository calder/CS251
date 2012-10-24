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


Token* token_create (TokenType type);
void token_free (Token* token);
void token_print (Token* token);
void token_print_parser (Token* token);

Token* tokenize_bool (const char* input, int start, int end);
Token* tokenize_float (const char* input, int start, int end);
Token* tokenize_fluff (const char* input, int start, int end);
Token* tokenize_int (const char* input, int start, int end);
Token* tokenize_paren (const char* input, int start, int end);
Token* tokenize_string (const char* input, int start, int end);
Token* tokenize_symbol (const char* input, int start, int end);


#endif