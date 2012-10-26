#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Interpreter/Value.h"


Value* value_create (ValueType type)
{
    Value* value = malloc(sizeof(Value));
    value->refCount = 1;
    value->type = type;
    return value;
}


void value_free (Value* value)
{
    assert(value->refCount == 0);
    if (value->type == STRING_VALUE) { free(value->stringVal); }
    if (value->type == SYMBOL_VALUE) { free(value->symbolVal); }
    free(value);
}


void value_reserve (Value* value)
{
    assert(value->refCount > 0);
    value->refCount += 1;
}


void value_release (Value* value)
{
    assert(value->refCount > 0);
    value->refCount -= 1;
    if (value->refCount <= 0) { value_free(value); }
}


void value_print (Value* value)
{
    // Placeholder
}