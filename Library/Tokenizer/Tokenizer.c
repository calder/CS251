#include <stdio.h>
#include <stdlib.h>
#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Tokens.h"
#include "Util/Quack.h"
#include "Util/StringUtil.h"
#include "Util/CharUtil.h"


Token* tokenize_from_start (const char* input, int start, int* cur);
Token* tokenize_from_bool_hash (const char* input, int start, int* cur);
Token* tokenize_from_bool_letter (const char* input, int start, int* cur);
Token* tokenize_from_int_sign (const char* input, int start, int* cur);
Token* tokenize_from_int_digit (const char* input, int start, int* cur);
Token* tokenize_from_float_dot (const char* input, int start, int* cur);
Token* tokenize_from_float_decimal (const char* input, int start, int* cur);
Token* tokenize_from_string_data (const char* input, int start, int* cur);
Token* tokenize_from_symbol (const char* input, int start, int* cur);
Token* tokenize_from_paren (const char* input, int start, int* cur);
Token* tokenize_from_whitespace (const char* input, int start, int* cur);
Token* tokenize_from_comment_data (const char* input, int start, int* cur);


Quack* tokenize (const char* input)
{
    Quack* tokens = quack_create();
    int start = 0, cur = 0;

    while (true)
    {
        Token* token = tokenize_from_start(input,start,&cur);
        start = cur;
        if (token == NULL)              { break; }
        if (token->type == END_TOKEN)   { free(token); break; }
        if (token->type == EMPTY_TOKEN) { free(token); continue; }
        quack_push_back(tokens,token);
    }

    return tokens;
}

void print_tokens (Quack* tokens)
{
    Quack* temp = quack_create();
    while (!quack_empty(tokens))
    {
        Token* token = quack_pop_front(tokens);
        quack_push_back(temp,token);
        print_token(token);
    }
    while (!quack_empty(temp))
    {
        quack_push_back(tokens, quack_pop_front(temp));
    }
    free(temp);
}


void print_token (Token* token)
{
    switch (token->type)
    {
        case BOOLEAN_TOKEN: printf("boolean: %s\n", token->boolData ? "#t" : "#f"); break;
        case INTEGER_TOKEN: printf("integer: %d\n", token->intData); break;
        case FLOAT_TOKEN:   printf("float:   %f\n", token->floatData); break;
        case STRING_TOKEN:  printf("string:  %s\n", token->stringData); break;
        case SYMBOL_TOKEN:  printf("symbol:  %s\n", token->symbolData); break;
        case PAREN_TOKEN:   printf("paren:   %c\n", token->parenData); break;
        default: break;
    }
}


Token* tokenize_from_start (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (c == 0)             { return token_create(END_TOKEN); }
    if (c == '#')           { return tokenize_from_bool_hash(input,start,cur); }
    if (c == '"')           { return tokenize_from_string_data(input,start,cur); }
    if (c == ';')           { return tokenize_from_comment_data(input,start,cur); }
    if (c == '.')           { return tokenize_from_float_dot(input,start,cur); }
    if (c == '+')           { return tokenize_from_int_sign(input,start,cur); }
    if (c == '-')           { return tokenize_from_int_sign(input,start,cur); }
    if (is_paren(c))        { return tokenize_from_paren(input,start,cur); }
    if (is_digit(c))        { return tokenize_from_int_digit(input,start,cur); }
    if (is_symbol_start(c)) { return tokenize_from_symbol(input,start,cur); }
    if (is_whitespace(c))   { return tokenize_from_whitespace(input,start,cur); }
    return NULL;
}


Token* tokenize_from_bool_hash (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if ((c == 't') || (c == 'f')) { return tokenize_from_bool_letter(input,start,cur); }
    return NULL;
}


Token* tokenize_from_bool_letter (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_finalizer(c)) { return tokenize_bool(input,start,--(*cur)); }
    return NULL;
}


Token* tokenize_from_int_sign (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c)) { return tokenize_from_int_digit(input,start,cur); }
    if (c == '.')    { return tokenize_from_float_dot(input,start,cur); }
    return NULL;
}


Token* tokenize_from_int_digit (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c))     { return tokenize_from_int_digit(input,start,cur); }
    if (c == '.')        { return tokenize_from_float_dot(input,start,cur); }
    if (is_finalizer(c)) { return tokenize_int(input,start,--(*cur)); }
    return NULL;
}


Token* tokenize_from_float_dot (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c)) { return tokenize_from_float_decimal(input,start,cur); }
    return NULL;
}


Token* tokenize_from_float_decimal (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c))     { return tokenize_from_float_decimal(input,start,cur); }
    if (is_finalizer(c)) { return tokenize_float(input,start,--(*cur)); }
    return NULL;
}


Token* tokenize_from_string_data (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (c == EOF) { return NULL; }
    if (c == '"') { return tokenize_string(input,start,*cur); }
    return tokenize_from_string_data(input,start,cur);
}


Token* tokenize_from_symbol (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_symbol_start(c) || is_digit(c)) { return tokenize_from_symbol(input,start,cur); }
    if (is_finalizer(c)) { return tokenize_symbol(input,start,--(*cur)); }
    return NULL;
}


Token* tokenize_from_paren (const char* input, int start, int* cur)
{
    return tokenize_paren(input,start,*cur);
}


Token* tokenize_from_whitespace (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_whitespace(c)) { return tokenize_from_whitespace(input,start,cur); }
    return tokenize_fluff(input,start,--(*cur));
}


Token* tokenize_from_comment_data (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if ((c == 0) || (c == '\n')) { return tokenize_fluff(input,start,*cur); }
    return tokenize_from_comment_data(input,start,cur);
}