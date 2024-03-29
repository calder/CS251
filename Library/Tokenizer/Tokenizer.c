#include <stdio.h>
#include <stdlib.h>
#include "Tokenizer/Tokenizer.h"
#include "Util/Quack.h"
#include "Util/StringUtil.h"
#include "Util/CharUtil.h"


Value* tokenize_from_start         (const char* input, int start, int* cur);
Value* tokenize_from_bool_hash     (const char* input, int start, int* cur);
Value* tokenize_from_bool_letter   (const char* input, int start, int* cur);
Value* tokenize_from_sign          (const char* input, int start, int* cur);
Value* tokenize_from_int_digit     (const char* input, int start, int* cur);
Value* tokenize_from_float_dot     (const char* input, int start, int* cur);
Value* tokenize_from_float_decimal (const char* input, int start, int* cur);
Value* tokenize_from_single        (const char* input, int start, int* cur);
Value* tokenize_from_string        (const char* input, int start, int* cur);
Value* tokenize_from_string_escape (const char* input, int start, int* cur);
Value* tokenize_from_symbol        (const char* input, int start, int* cur);
Value* tokenize_from_paren         (const char* input, int start, int* cur);
Value* tokenize_from_whitespace    (const char* input, int start, int* cur);
Value* tokenize_from_comment       (const char* input, int start, int* cur);

Value* tokenize_bool   (const char* input, int start, int end);
Value* tokenize_float  (const char* input, int start, int end);
Value* tokenize_fluff  (const char* input, int start, int end);
Value* tokenize_int    (const char* input, int start, int end);
Value* tokenize_paren  (const char* input, int start, int end);
Value* tokenize_string (const char* input, int start, int end);
Value* tokenize_symbol (const char* input, int start, int end);


Quack* tokenize (const char* input)
{
    Quack* tokens = quack_create();
    int start = 0, cur = 0;

    while (true)
    {
        Value* token = tokenize_from_start(input,start,&cur);
        start = cur;
        if (token == NULL)              { goto syntax_error; }
        if (token->type == END_TOKEN)   { free(token); break; }
        if (token->type == NULL_TOKEN)  { free(token); continue; }
        quack_push_back(tokens,token);
    }

    return tokens;

syntax_error:
    
    while (!quack_empty(tokens)) { value_release(quack_pop_front(tokens)); }
    quack_free(tokens);
    return NULL;
}


void print_tokens (Quack* tokens)
{
    Quack* temp = quack_create();
    while (!quack_empty(tokens))
    {
        Value* token = quack_pop_front(tokens);
        quack_push_back(temp,token);
        token_print(token);
    }
    while (!quack_empty(temp))
    {
        quack_push_back(tokens, quack_pop_front(temp));
    }
    quack_free(temp);
}


Value* tokenize_from_start (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (c == 0)             { return value_create(END_TOKEN); }
    if (c == '#')           { return tokenize_from_bool_hash(input,start,cur); }
    if (c == '"')           { return tokenize_from_string(input,start,cur); }
    if (c == ';')           { return tokenize_from_comment(input,start,cur); }
    if (c == '.')           { return tokenize_from_float_dot(input,start,cur); }
    if (c == '+')           { return tokenize_from_sign(input,start,cur); }
    if (c == '-')           { return tokenize_from_sign(input,start,cur); }
    if (c == '*')           { return tokenize_from_single(input,start,cur); }
    if (c == '/')           { return tokenize_from_single(input,start,cur); }
    if (is_paren(c))        { return tokenize_from_paren(input,start,cur); }
    if (is_digit(c))        { return tokenize_from_int_digit(input,start,cur); }
    if (is_symbol_start(c)) { return tokenize_from_symbol(input,start,cur); }
    if (is_whitespace(c))   { return tokenize_from_whitespace(input,start,cur); }
    return NULL;
}


Value* tokenize_from_bool_hash (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if ((c == 't') || (c == 'f')) { return tokenize_from_bool_letter(input,start,cur); }
    return NULL;
}


Value* tokenize_from_bool_letter (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_finalizer(c)) { return tokenize_bool(input,start,--(*cur)); }
    return NULL;
}


Value* tokenize_from_int_digit (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c))     { return tokenize_from_int_digit(input,start,cur); }
    if (c == '.')        { return tokenize_from_float_dot(input,start,cur); }
    if (is_finalizer(c)) { return tokenize_int(input,start,--(*cur)); }
    return NULL;
}


Value* tokenize_from_float_dot (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c)) { return tokenize_from_float_decimal(input,start,cur); }
    return NULL;
}


Value* tokenize_from_float_decimal (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c))     { return tokenize_from_float_decimal(input,start,cur); }
    if (is_finalizer(c)) { return tokenize_float(input,start,--(*cur)); }
    return NULL;
}


Value* tokenize_from_sign (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_digit(c))     { return tokenize_from_int_digit(input,start,cur); }
    if (c == '.')        { return tokenize_from_float_dot(input,start,cur); }
    if (is_finalizer(c)) { return tokenize_symbol(input,start,--(*cur)); }
    return NULL;
}


Value* tokenize_from_single (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_finalizer(c)) { return tokenize_symbol(input,start,--(*cur)); }
    return NULL;
}


Value* tokenize_from_string (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (c == 0)    { return NULL; }
    if (c == EOF)  { return NULL; }
    if (c == '\n') { return NULL; }
    if (c == '"')  { return tokenize_string(input,start+1,*cur-1); }
    if (c == '\\') { return tokenize_from_string_escape(input,start,cur); }
    return tokenize_from_string(input,start,cur);
}


Value* tokenize_from_string_escape (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (c == 0)    { return NULL; }
    if (c == EOF)  { return NULL; }
    if (c == '\n') { return NULL; }
    if (c == '"')  { return tokenize_from_string(input,start,cur); }
    if (c == '\\') { return tokenize_from_string(input,start,cur); }
    if (c == 'n')  { return tokenize_from_string(input,start,cur); }
    if (c == 't')  { return tokenize_from_string(input,start,cur); }
    return NULL;
}


Value* tokenize_from_symbol (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_symbol_body(c)) { return tokenize_from_symbol(input,start,cur); }
    if (is_finalizer(c))   { return tokenize_symbol(input,start,--(*cur)); }
    return NULL;
}


Value* tokenize_from_paren (const char* input, int start, int* cur)
{
    return tokenize_paren(input,start,*cur);
}


Value* tokenize_from_whitespace (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if (is_whitespace(c)) { return tokenize_from_whitespace(input,start,cur); }
    return tokenize_fluff(input,start,--(*cur));
}


Value* tokenize_from_comment (const char* input, int start, int* cur)
{
    char c = input[(*cur)++];
    if ((c == 0) || (c == '\n')) { return tokenize_fluff(input,start,--(*cur)); }
    return tokenize_from_comment(input,start,cur);
}


Value* tokenize_bool (const char* input, int start, int cur)
{
    Value* value = value_create(BOOLEAN_VALUE);
    value->boolVal = input[start+1] == 't';
    return value;
}


Value* tokenize_float (const char* input, int start, int cur)
{
    Value* value = value_create(FLOAT_VALUE);
    char* string = substring(input,start,cur);
    sscanf(string, "%f", &value->floatVal);
    free(string);
    return value;
}


Value* tokenize_fluff (const char* input, int start, int cur)
{
    Value* value = malloc(sizeof(Value));
    value->type = NULL_TOKEN;
    return value;
}


Value* tokenize_int (const char* input, int start, int cur)
{
    Value* value = value_create(INTEGER_VALUE);
    char* string = substring(input,start,cur);
    sscanf(string, "%d", &value->intVal);
    free(string);
    return value;
}


Value* tokenize_paren (const char* input, int start, int cur)
{
    Value* value = value_create(PAREN_TOKEN);
    value->paren = input[start];
    return value;
}


Value* tokenize_string (const char* input, int start, int cur)
{
    Value* value = value_create(STRING_VALUE);
    value->string = malloc(sizeof(char) * (cur - start + 1));
    int j = 0;
    for (int i = start; i < cur; ++i)
    {
        if (input[i] == '\\')
        {
            ++i;
            if (input[i] == 'n') { value->string[j++] = '\n'; continue; }
            if (input[i] == 't') { value->string[j++] = '\t'; continue; }
        }
        value->string[j++] = input[i];
    }
    value->string[j] = 0;
    return value;
}


Value* tokenize_symbol (const char* input, int start, int cur)
{
    Value* value = value_create(SYMBOL_VALUE);
    value->string = substring(input,start,cur);
    return value;
}