#include <stdlib.h>
#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Tokens.h"
#include "Util/Quack.h"
#include "Util/StringUtil.h"
#include "Util/CharUtil.h"



Token* tokenize_from_start (char* input, int start, int* cur);
Token* tokenize_from_bool_hash (char* input, int start, int* cur);
Token* tokenize_from_bool_letter (char* input, int start, int* cur);
Token* tokenize_from_int_sign (char* input, int start, int* cur);
Token* tokenize_from_int_digit (char* input, int start, int* cur);
Token* tokenize_from_float_dot (char* input, int start, int* cur);
Token* tokenize_from_float_decimal (char* input, int start, int* cur);
Token* tokenize_from_string_data (char* input, int start, int* cur);
Token* tokenize_from_symbol (char* input, int start, int* cur);
Token* tokenize_from_paren (char* input, int start, int* cur);
Token* tokenize_from_whitespace (char* input, int start, int* cur);
Token* tokenize_from_comment_data (char* input, int start, int* cur);


Quack* tokenize (char* input)
{
    Quack* tokens = quack_create();
    int start = 0, cur = 0;

    while (true)
    {
        Token* token = tokenize_from_start(input,0,&cur);
        if (token == NULL) { break; }
        if (token->type == EMPTY_TOKEN) { free(token); continue; }
        quack_push_back(tokens,token);
        start = cur - 1;
    }

    return tokens;
}


void print_tokens (Quack* tokens)
{
    while (!quack_empty(tokens))
    {
        Token* token = quack_pop_front(tokens);
        print_token(token);
        free(token);
    }
}


void print_token (Token* token)
{
    // Placeholder
}


Token* tokenize_from_start (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (c == '#')           { return tokenize_from_bool_hash(input,start,cur); }
    if (c == '"')           { return tokenize_from_string_data(input,start,cur); }
    if (c == ';')           { return tokenize_from_comment_data(input,start,cur); }
    if (c == '.')           { return tokenize_from_float_dot(input,start,cur); }
    if (c == '+')           { return tokenize_from_int_sign(input,start,cur); }
    if (c == '-')           { return tokenize_from_int_sign(input,start,cur); }
    if (is_paren(c))        { return tokenize_from_paren(input,start,cur); }
    if (is_digit(c))        { return tokenize_from_int_digit(input,start,cur); }
    if (is_symbol_start(c)) { return tokenize_from_symbol(input,start,cur); }
    return NULL;
}


Token* tokenize_from_bool_hash (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if ((c == 't') || (c == 'f')) { return tokenize_from_bool_letter(input,start,cur); }
    return NULL;
}


Token* tokenize_from_bool_letter (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_finalizer(c)) { return tokenize_bool(input,start,--(*cur)); }
    return NULL;
}


Token* tokenize_from_int_sign (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c)) { return tokenize_from_int_digit(input,start,cur); }
    return NULL;
}


Token* tokenize_from_int_digit (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c))     { return tokenize_from_int_digit(input,start,cur); }
    if (c == '.')        { return tokenize_from_float_dot(input,start,cur); }
    if (is_finalizer(c)) { return tokenize_int(input,start,--(*cur)); }
    return NULL;
}


Token* tokenize_from_float_dot (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c)) { return tokenize_from_float_decimal(input,start,cur); }
    return NULL;
}


Token* tokenize_from_float_decimal (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c))     { return tokenize_from_float_decimal(input,start,cur); }
    if (is_finalizer(c)) { return tokenize_float(input,start,--(*cur)); }
    return NULL;
}


Token* tokenize_from_string_data (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_letter(c))     { return tokenize_from_string_data(input,start,cur); }
    if (is_whitespace(c)) { return tokenize_from_string_data(input,start,cur); }
    if (c == '"')         { return tokenize_string(input,start,--(*cur)); }
    return NULL;
}


Token* tokenize_from_symbol (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_symbol_start(c) || is_digit(c)) { return tokenize_from_symbol(input,start,cur); }
    if (is_finalizer(c)) { return tokenize_symbol(input,start,--(*cur)); }
    return NULL;
}


Token* tokenize_from_paren (char* input, int start, int* cur) 
{
    return tokenize_paren(input,start,cur);
}


Token* tokenize_from_whitespace (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_whitespace(c)) { return tokenize_from_whitespace(input,start,cur); }
    return tokenize_fluff(input,start,--(*cur));
}


Token* tokenize_from_comment_data (char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (c != '\n') { return tokenize_from_comment_data(input,start,cur); }
    return tokenize_fluff(input,start,--(*cur));
}