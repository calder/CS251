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
        }
        break;
    case EXPRESSION_VALUE:
        parsetree_release(value->exprVal);
        break;
    case STRING_VALUE:
        free(value->stringVal);
        break;
    default:
        break;
    }

    free(value);
}


void value_reserve (Value* value)
{
    value->refCount += 1;
}


void value_release (Value* value)
{
    value->refCount -= 1;
    if (value->refCount <= 0) { value_free(value); }
}


void value_print (Value* value)
{
    switch (value->type)
    {
        case BOOLEAN_VALUE:  printf("%s ", value->boolVal ? "#t" : "#f"); break;
        case INTEGER_VALUE:  printf("%d ", value->intVal); break;
        case FLOAT_VALUE:    printf("%f ", value->floatVal); break;
        case FUNCTION_VALUE: printf("lambda "); break;
        case STRING_VALUE:   printf("%s ", value->stringVal); break;
        default:             printf("??? "); break;
    }
}


Value* value_create_expression (ParseTree* parseTree)
{
    Value* value = value_create(EXPRESSION_VALUE);
    value->exprVal = parseTree;
    parsetree_reserve(value->exprVal);
    return value;
}


Value* value_create_function_builtin (struct Environment* environment, Value*(*function)(Closure*,ParseTree*))
{
    Value* value = value_create(FUNCTION_VALUE);
    value->funcVal.function = function;
    value->funcVal.environment = environment;
    value->funcVal.parseTree = NULL;
    environment_reserve(environment);
    return value;
}


Value* value_create_function_scheme (struct Environment* environment, ParseTree* parseTree)
{
    Value* value = value_create(FUNCTION_VALUE);
    value->funcVal.function = &function_lambda;
    value->funcVal.environment = environment;
    value->funcVal.parseTree = parseTree;
    environment_reserve(environment);
    parsetree_reserve(parseTree);
    return value;
}