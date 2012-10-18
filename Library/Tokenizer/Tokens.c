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


Token* tokenize_bool (char* input, int start, int cur)
{
    Token* token = token_create(BOOLEAN_TOKEN);
    token->boolData = input[start+1] == 't';
    return token;
}


Token* tokenize_int (char* input, int start, int cur)
{
    Token* token = token_create(INTEGER_TOKEN);
    char* string = substring(input,start,cur);
    sscanf(string, "%d", &token->intData);
    free(string);
    return token;
}


Token* tokenize_float (char* input, int start, int cur)
{
    Token* token = token_create(FLOAT_TOKEN);
    char* string = substring(input,start,cur);
    sscanf(string, "%f", &token->floatData);
    free(string);
    return token;
}


Token* tokenize_string (char* input, int start, int cur)
{
    Token* token = token_create(STRING_TOKEN);
    token->stringData = substring(input,start,cur);
    return token;
}


Token* tokenize_symbol (char* input, int start, int cur)
{
    Token* token = token_create(SYMBOL_TOKEN);
    token->stringData = substring(input,start,cur);
    return token;
}


Token* tokenize_paren (char* input, int start, int cur)
{
    char c = input[start];
    Token* token = token_create(OPAREN_TOKEN);
    if ((c == ')') || (c == ']')) { token->type = CPAREN_TOKEN; }
    return token;
}


Token* tokenize_fluff (char* input, int start, int cur)
{
    Token* token = malloc(sizeof(Token));
    token->type = EMPTY_TOKEN;
    return token;
}