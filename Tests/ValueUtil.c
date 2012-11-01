#include <assert.h>
#include <string.h>
#include "Tokenizer/Tokenizer.h"
#include "ValueUtil.h"


void check_bool (Value* value, bool expected)
{
    assert(value != NULL);
    assert(value->type == BOOLEAN_VALUE);
    assert(value->boolVal == expected);
}


void check_float (Value* value, float expected)
{
    assert(value != NULL);
    assert(value->type == FLOAT_VALUE);
    assert(value->floatVal == expected);
}


void check_int (Value* value, int expected)
{
    assert(value != NULL);
    assert(value->type == INTEGER_VALUE);
    assert(value->intVal == expected);
}


void check_list (Value* value)
{
    assert(value != NULL);
    assert(value->type == LIST_VALUE);
}


void check_paren (Value* value, char expected)
{
    assert(value != NULL);
    assert(value->type == PAREN_TOKEN);
    assert(value->paren == expected);
}


void check_string (Value* value, char* expected)
{
    assert(value != NULL);
    assert(value->type == STRING_VALUE);
    assert(!strcmp(value->string,expected));
}


void check_symbol (Value* value, char* expected)
{
    assert(value != NULL);
    assert(value->type == SYMBOL_VALUE);
    assert(!strcmp(value->symbol,expected));
}


void check_and_free_bool (Value* value, bool expected)
{
    check_bool(value, expected);
    value_release(value);
}


void check_and_free_float (Value* value, float expected)
{
    check_float(value,expected);
    value_release(value);
}


void check_and_free_int (Value* value, int expected)
{
    check_int(value,expected);
    value_release(value);
}


void check_and_free_list (Value* value)
{
    check_list(value);
    value_release(value);
}


void check_and_free_paren (Value* value, char expected)
{
    check_paren(value,expected);
    value_release(value);
}


void check_and_free_string (Value* value, char* expected)
{
    check_string(value,expected);
    value_release(value);
}


void check_and_free_symbol (Value* value, char* expected)
{
    check_symbol(value,expected);
    value_release(value);
}