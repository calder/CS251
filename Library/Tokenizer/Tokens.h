#ifndef TOKENS_H
#define TOKENS_H


/// All accepted token types
enum
{
    ZERO,
    BOOLEAN,
    INTEGER,
    FLOAT,
    STRING,
    SYMBOL,
    OPEN,
    CLOSE
}
typedef TokenType;


/// All accepted token data
union
{
}
typedef TokenData;


/// A single "word" or "punctuation mark" in a program
struct
{
    TokenType type;
    char* value;
}
typedef Token;


Token* tokenize_bool (char* input);
Token* tokenize_int (char* input);
Token* tokenize_float (char* input);
Token* tokenize_string (char* input);
Token* tokenize_symbol (char* input);
Token* tokenize_paren (char* input);


#endif