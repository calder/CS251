#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Interpreter/Functions.h"
#include "Interpreter/Interpreter.h"
#include "Tokenizer/Value.h"
#include "Parser/Parser.h"
#include "Util/StringUtil.h"


Value* evaluate_function (ParseTree* parseTree, Environment* environment);
Value* evaluate_primitive (ParseTree* parseTree, Environment* environment);

Value* evaluate_lambda (Value* lambda, ParseTree* args);


Quack* interpret (const char* input)
{
    // Parse input into expression trees
    Environment* environment = environment_create_default();
    Quack* values = quack_create();
    Quack* expressions = parse(input);

    // Evaluate each expression tree
    while (!quack_empty(expressions))
    {
        ParseTree* parseTree = quack_pop_front(expressions);
        Value* value = evaluate(parseTree, environment);
        parsetree_release(parseTree);
        quack_push_back(values, value);
    }

    // Clean up and return evaluated expressions
    environment_release(environment);
    quack_free(expressions);
    return values;
}


Value* evaluate (ParseTree* parseTree, Environment* environment)
{
    if (parseTree->token != NULL) { return evaluate_primitive(parseTree,environment); }
    else                          { return evaluate_function(parseTree,environment); }
}


Value* evaluate_list (ParseTree* parseTree)
{
    // Primitive case (leaf)
    if (parseTree->token != NULL) { return evaluate_primitive(parseTree,NULL); }

    // List construction (subtree)
    Value* list = value_create_list_empty();
    for (int i = parseTree->numChildren - 1; i >= 0; --i)
    {
        Value* item = evaluate_list(parseTree->children[i]);
        if (item == NULL) { value_release(list); return NULL; }
        Value* head = value_create(LIST_VALUE);
        head->head = item;
        head->tail = list;
        list = head;
    }
    return list;
}


Value* evaluate_function (ParseTree* parseTree, Environment* environment)
{
    // Check number of arguments
    if (parseTree->numChildren < 1) { return NULL; }

    // Evaluate the first argument (which is hopefully a function)
    Value* f = evaluate(parseTree->children[0], environment);
    if (f == NULL) { return NULL; }

    // Apply function and return result
    Value* result = NULL;
    if (f->type == FUNCTION_VALUE) { result = f->function(environment, parseTree); }
    if (f->type == LAMBDA_VALUE)   { result = evaluate_lambda(f, parseTree); }
    value_release(f);
    return result;
}


Value* evaluate_primitive (ParseTree* parseTree, Environment* environment)
{
    Value* token = parseTree->token;
    Value* value;

    switch (token->type)
    {
    case BOOLEAN_VALUE:
        value = value_create(BOOLEAN_VALUE);
        value->boolVal = token->boolVal;
        break;
    case FLOAT_VALUE:
        value = value_create(FLOAT_VALUE);
        value->floatVal = token->floatVal;
        break;
    case INTEGER_VALUE:
        value = value_create(INTEGER_VALUE);
        value->intVal = token->intVal;
        break;
    case STRING_VALUE:
        value = value_create(STRING_VALUE);
        value->string = dupstring(token->string);
        break;
    case SYMBOL_VALUE:
        if (environment == NULL)
        {
            value = value_create(SYMBOL_VALUE);
            value->symbol = dupstring(token->symbol);
        }
        else
        {
            value = environment_get(environment, token->symbol);
            if (value != NULL) { value_reserve(value); }
        }
        break;
    default:
        assert(false);
    }

    return value;
}


Value* evaluate_lambda (Value* lambda, ParseTree* args)
{
    return NULL; // Placeholder
}