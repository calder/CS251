#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Interpreter/Environment.h"
#include "Interpreter/Functions.h"
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
    switch (value->type)
    {
    case FUNCTION_VALUE:
        environment_release(value->funcVal.environment);
        if (value->funcVal.parseTree != NULL)
        {
            parsetree_release(value->funcVal.parseTree);
            for (int i = 0; i < value->funcVal.numParams; ++i)
            {
                free(value->funcVal.params[i]);
            }
            free(value->funcVal.params);
        }
        break;
    case LIST_VALUE:
        value_release(value->listVal.head);
        value_release(value->listVal.tail);
        break;
    case STRING_VALUE:
        free(value->stringVal);
        break;
    case SYMBOL_VALUE:
        free(value->symbolVal);
        break;
    default:
        break;
    }

    free(value);
}


void value_reserve (Value* value)
{
    if (value == NULL) { return; }
    value->refCount += 1;
}


void value_release (Value* value)
{
    if (value == NULL) { return; }
    value->refCount -= 1;
    if (value->refCount <= 0) { value_free(value); }
}


void value_print (Value* value)
{
    if (value == NULL) { return; }
    switch (value->type)
    {
        case BOOLEAN_VALUE:  printf("%s ", value->boolVal ? "#t" : "#f"); break;
        case FLOAT_VALUE:    printf("%f ", value->floatVal); break;
        case FUNCTION_VALUE: printf("lambda "); break;
        case INTEGER_VALUE:  printf("%d ", value->intVal); break;
        case LIST_VALUE:     printf("list "); break;
        case STRING_VALUE:   printf("\"%s\" ", value->stringVal); break;
        case SYMBOL_VALUE:   printf("%s ", value->stringVal); break;
        default:             printf("??? "); break;
    }
}


Value* value_create_function (struct Environment* environment, Value*(*function)(Closure*,ParseTree*))
{
    Value* value = value_create(FUNCTION_VALUE);
    value->funcVal.function = function;
    value->funcVal.environment = environment;
    value->funcVal.parseTree = NULL;
    environment_reserve(environment);
    return value;
}


Value* value_create_list_empty ()
{
    Value* value = value_create(LIST_VALUE);
    value->listVal.head = NULL;
    value->listVal.tail = NULL;
    return value;
}