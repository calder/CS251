#include <assert.h>
#include <string.h>
#include "Interpreter/Value.h"


void check_bool_value (Value* value, bool boolVal)
{
    assert(value != NULL);
    assert(value->type == BOOLEAN_VALUE);
    assert(value->boolVal == boolVal);
}


void check_float_value (Value* value, float floatVal)
{
    assert(value != NULL);
    assert(value->type == FLOAT_VALUE);
    assert(value->floatVal == floatVal);
}


void check_int_value (Value* value, int intVal)
{
    assert(value != NULL);
    assert(value->type == INTEGER_VALUE);
    assert(value->intVal == intVal);
}


void check_lambda_value (Value* value)
{
    assert(value != NULL);
    assert(value->type == LIST_VALUE);
}


void check_list_value (Value* value)
{
    assert(value != NULL);
    assert(value->type == LIST_VALUE);
}


void check_string_value (Value* value, char* stringVal)
{
    assert(value != NULL);
    assert(value->type == STRING_VALUE);
    assert(!strcmp(value->stringVal, stringVal));
}


void check_symbol_value (Value* value, char* symbolVal)
{
    assert(value != NULL);
    assert(value->type == SYMBOL_VALUE);
    assert(!strcmp(value->symbolVal, symbolVal));
}