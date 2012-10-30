#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Interpreter/Functions.h"
#include "Interpreter/Interpreter.h"
#include "Interpreter/PsuedoFunctions.h"
#include "Interpreter/Value.h"
#include "Parser/Parser.h"
#include "Tokenizer/Tokens.h"
#include "Util/StringUtil.h"


Value* evaluate_function (ParseTree* parseTree, Environment* environment);
Value* evaluate_primitive (ParseTree* parseTree, Environment* environment);


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
    // Primitive case (leaf)
    if (parseTree->token != NULL) { return evaluate_primitive(parseTree,environment); }

    // Function application case (subtree)
    return evaluate_function(parseTree,environment);
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
        head->listVal.head = item;
        head->listVal.tail = list;
        list = head;
    }
    return list;
}


Value* evaluate_function (ParseTree* parseTree, Environment* environment)
{
    // Check number of arguments
    if (parseTree->numChildren < 1) { return NULL; }

    // Special case out psuedo-functions (herp derp Scheme)
    if (parseTree->children[0]->token != NULL &&
        parseTree->children[0]->token->type == SYMBOL_TOKEN)
    {
        if (!strcmp(parseTree->children[0]->token->symbolVal, "if"))
            { return function_if(environment,parseTree); }
        if (!strcmp(parseTree->children[0]->token->symbolVal, "lambda"))
            { return function_lambda(environment,parseTree); }
        if (!strcmp(parseTree->children[0]->token->symbolVal, "let"))
            { return function_let(environment,parseTree); }
        if (!strcmp(parseTree->children[0]->token->symbolVal, "quote"))
            { return function_quote(environment,parseTree); }
    }

    // Evaluate the first argument (which is hopefully a function)
    Value* f = evaluate(parseTree->children[0], environment);
    if (f->type != FUNCTION_VALUE) { value_release(f); return NULL; }

    // Apply the first argument as a function
    Value* result = f->funcVal.function(&f->funcVal, parseTree);
    value_release(f);
    return result;
}


Value* evaluate_primitive (ParseTree* parseTree, Environment* environment)
{
    Token* token = parseTree->token;
    Value* value;

    switch (token->type)
    {
    case BOOLEAN_TOKEN:
        value = value_create(BOOLEAN_VALUE);
        value->boolVal = token->boolVal;
        break;
    case FLOAT_TOKEN:
        value = value_create(FLOAT_VALUE);
        value->floatVal = token->floatVal;
        break;
    case INTEGER_TOKEN:
        value = value_create(INTEGER_VALUE);
        value->intVal = token->intVal;
        break;
    case STRING_TOKEN:
        value = value_create(STRING_VALUE);
        value->stringVal = dupstring(token->stringVal);
        break;
    case SYMBOL_TOKEN:
        if (environment == NULL)
        {
            value = value_create(SYMBOL_VALUE);
            value->symbolVal = dupstring(token->symbolVal);
        }
        else
        {
            value = environment_get(environment, token->symbolVal);
            value_reserve(value);
        }
        break;
    default:
        assert(false);
    }

    return value;
}