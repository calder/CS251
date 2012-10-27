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
    switch (value->type)
    {
        case BOOLEAN_VALUE: printf("%s ", value->boolVal ? "#t" : "#f"); break;
        case INTEGER_VALUE: printf("%d ", value->intVal); break;
        case FLOAT_VALUE:   printf("%f ", value->floatVal); break;
        case LAMBDA_VALUE:  printf("lambda "); break;
        case STRING_VALUE:  printf("%s ", value->stringVal); break;
        default:            printf("??? "); break;
    }
}