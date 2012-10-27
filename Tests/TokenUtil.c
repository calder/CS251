#include <assert.h>
#include <string.h>
#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Tokens.h"
#include "TokenUtil.h"


void check_bool (Token* token, bool value)
{
    assert(token->type == BOOLEAN_TOKEN);
    assert(token->boolVal == value);
}


void check_float (Token* token, float value)
{
    assert(token->type == FLOAT_TOKEN);
    assert(token->floatVal == value);
}


void check_int (Token* token, int value)
{
    assert(token->type == INTEGER_TOKEN);
    assert(token->intVal == value);
}


void check_paren (Token* token, char value)
{
    assert(token->type == PAREN_TOKEN);
    assert(token->parenVal == value);
}


void check_string (Token* token, char* value)
{
    assert(token->type == STRING_TOKEN);
    assert(!strcmp(token->stringVal,value));
}


void check_symbol (Token* token, char* value)
{
    assert(token->type == SYMBOL_TOKEN);
    assert(!strcmp(token->symbolVal,value));
}


void check_and_free_bool (Token* token, bool value)
{
    check_bool(token, value);
    token_free(token);
}


void check_and_free_float (Token* token, float value)
{
    check_float(token,value);
    token_free(token);
}


void check_and_free_int (Token* token, int value)
{
    token_free(token);
}


void check_and_free_paren (Token* token, char value)
{
    check_paren(token,value);
    token_free(token);
}


void check_and_free_string (Token* token, char* value)
{
    check_string(token,value);
    token_free(token);
}


void check_and_free_symbol (Token* token, char* value)
{
    check_symbol(token,value);
    token_free(token);
}