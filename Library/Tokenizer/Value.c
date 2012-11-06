#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Interpreter/Environment.h"
#include "Parser/ParseTree.h"
#include "Tokenizer/Value.h"
#include "Util/StringUtil.h"


void value_free (Value* value);
void value_print_lambda (Value* lambda);
void value_print_list (Value* list);


Value* value_create (ValueType type)
{
    Value* value = malloc(sizeof(Value));
    value->refCount = 1;
    value->type = type;
    return value;
}


Value* value_create_bool (bool b)
{
    Value* value = value_create(BOOLEAN_VALUE);
    value->boolVal = b;
    return value;
}


Value* value_create_float (float x)
{
    Value* value = value_create(FLOAT_VALUE);
    value->floatVal = x;
    return value;
}


Value* value_create_function (Value* (*func) (Environment*, ParseTree*))
{
    Value* value = value_create(FUNCTION_VALUE);
    value->function = func;
    value->keyword = false;
    return value;
}


Value* value_create_int (int x)
{
    Value* value = value_create(INTEGER_VALUE);
    value->intVal = x;
    return value;
}


Value* value_create_keyword (Value* (*func) (Environment*, ParseTree*))
{
    Value* value = value_create(FUNCTION_VALUE);
    value->function = func;
    value->keyword = true;
    return value;
}


Value* value_create_lambda (Environment* environment, int numParams, char** params, ParseTree* code)
{
    Value* value = value_create(LAMBDA_VALUE);
    value->environment = environment;
    value->numParams = numParams;
    value->params = params;
    value->code = code;
    environment_reserve(environment);
    parsetree_reserve(code);
    return value;
}


Value* value_create_list_empty ()
{
    Value* value = value_create(LIST_VALUE);
    value->head = NULL;
    value->tail = NULL;
    return value;
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


void value_free (Value* value)
{
    switch (value->type)
    {
    case FUNCTION_VALUE:
        environment_release(value->environment);
        break;
    case LAMBDA_VALUE:
        parsetree_release(value->code);
        environment_release(value->environment);
        for (int i = 0; i < value->numParams; ++i) { free(value->params[i]); }
        free(value->params);
        break;
    case LIST_VALUE:
        if (value->head != NULL) { value_release(value->head); }
        if (value->tail != NULL) { value_release(value->tail); }
        break;
    case STRING_VALUE:
        free(value->string);
        break;
    case SYMBOL_VALUE:
        free(value->symbol);
        break;
    default:
        break;
    }

    free(value);
}


void value_print (Value* value)
{
    if (value == NULL) { return; }
    switch (value->type)
    {
        case BOOLEAN_VALUE:  printf("%s ", value->boolVal ? "#t" : "#f"); break;
        case FLOAT_VALUE:    printf("%f ", value->floatVal); break;
        case FUNCTION_VALUE: printf("#<procedure> "); break;
        case INTEGER_VALUE:  printf("%d ", value->intVal); break;
        case LAMBDA_VALUE:   printf("#<procedure> "); break;
        case LIST_VALUE:     value_print_list(value); break;
        case STRING_VALUE:   printf("\"%s\" ", value->string); break;
        case SYMBOL_VALUE:   printf("%s ", value->string); break;
        default:             printf("??? "); break;
    }
}


void value_print_debug (Value* value)
{
    if (value == NULL) { return; }
    switch (value->type)
    {
        case BOOLEAN_VALUE:  printf("BOOLEAN_VALUE: %s ", value->boolVal ? "#t" : "#f"); break;
        case FLOAT_VALUE:    printf("FLOAT_VALUE: %f ", value->floatVal); break;
        case FUNCTION_VALUE: printf("func "); break;
        case INTEGER_VALUE:  printf("INTEGER_VALUE: %d ", value->intVal); break;
        case LAMBDA_VALUE:   value_print_lambda(value); break;
        case LIST_VALUE:     value_print_list(value); break;
        case STRING_VALUE:   printf("STRING_VALUE: \"%s\" ", value->string); break;
        case SYMBOL_VALUE:   printf("SYMBOL_VALUE: %s ", value->string); break;
        case UNDEF_VALUE:    printf("UNDEFINED_VALUE"); break;
        default:             printf("??? "); break;
    }
}


void value_print_lambda (Value* lambda)
{
    printf("( lambda ");
    printf("( ");
    for (int i = 0; i < lambda->numParams; ++i)
    {
        printf("%s ", lambda->params[i]);
    }
    printf(") ");
    parsetree_print(lambda->code);
    printf(") ");
}


void value_print_list (Value* list)
{
    printf("( ");
    while (list->head != NULL)
    {
        value_print(list->head);
        list = list->tail;
    }
    printf(") ");
}


void token_print (Value* value)
{
    switch (value->type)
    {
        case BOOLEAN_VALUE: printf("boolean : %s\n", value->boolVal ? "#t" : "#f"); break;
        case INTEGER_VALUE: printf("integer : %d\n", value->intVal); break;
        case FLOAT_VALUE:   printf("  float : %f\n", value->floatVal); break;
        case STRING_VALUE:  printf(" string : %s\n", value->string); break;
        case SYMBOL_VALUE:  printf(" symbol : %s\n", value->symbol); break;
        case PAREN_TOKEN:   printf("  paren : %c\n", value->paren); break;
        default:            printf("NOT A TOKEN\n"); break;
    }
}