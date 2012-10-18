#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Tokenizer/Tokens.h"
#include "Util/StringUtil.h"


Token* token_create (TokenType type)
{
    Token* token = malloc(sizeof(Token));
    token->type = type;
    return token;
}


Token* tokenize_bool (const char* input, int start, int cur)
{
    Token* token = token_create(BOOLEAN_TOKEN);
    token->boolData = input[start+1] == 't';
    return token;
}


Token* tokenize_int (const char* input, int start, int cur)
{
    Token* token = token_create(INTEGER_TOKEN);
    char* string = substring(input,start,cur);
    sscanf(string, "%d", &token->intData);
    free(string);
    return token;
}


Token* tokenize_float (const char* input, int start, int cur)
{
    Token* token = token_create(FLOAT_TOKEN);
    char* string = substring(input,start,cur);
    sscanf(string, "%f", &token->floatData);
    free(string);
    return token;
}


Token* tokenize_fluff (const char* input, int start, int cur)
{
    Token* token = malloc(sizeof(Token));
    token->type = EMPTY_TOKEN;
    return token;
}


Token* tokenize_paren (const char* input, int start, int cur)
{
    Token* token = token_create(PAREN_TOKEN);
    token->parenData = input[start];
    return token;
}


Token* tokenize_string (const char* input, int start, int cur)
{
    Token* token = token_create(STRING_TOKEN);
    token->stringData = substring(input,start,cur);
    return token;
}


Token* tokenize_symbol (const char* input, int start, int cur)
{
    Token* token = token_create(SYMBOL_TOKEN);
    token->stringData = substring(input,start,cur);
    return token;
}