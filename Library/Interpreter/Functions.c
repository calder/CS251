#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Interpreter/Interpreter.h"
#include "Interpreter/Functions.h"
#include "Parser/Parser.h"
#include "Util/Stringbuffer.h"


Value* function_define (Environment* environment, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren != 3) { return NULL; }
    ParseTree* var = args->children[1];
    ParseTree* val = args->children[2];

    if (var->token == NULL || var->token->type != SYMBOL_VALUE) { return NULL; }

    Value* value = evaluate(val, environment);
    if (value == NULL) { return NULL; }
    environment_set(environment, var->token->symbol, value);
    value_release(value);

    return value_create(NULL_VALUE);
}


Value* function_if (Environment* environment, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren != 4) { return NULL; }

    // Evaluate and check condition
    Value* condition = evaluate(args->children[1], environment);
    if (condition == NULL) { return NULL; }
    if (condition->type != BOOLEAN_VALUE) { value_release(condition); return NULL; }

    // Evaluate and return the right case
    bool cond = condition->boolVal;
    value_release(condition);
    if (cond) { return evaluate(args->children[2], environment); }
    else      { return evaluate(args->children[3], environment); }
}


Value* function_lambda (Environment* environment, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren != 3) { return NULL; }

    // Check parameter list
    for (int i = 0; i < args->children[1]->numChildren; ++i)
    {
        if (args->children[1]->children[i]->token == NULL) { return NULL; }
        if (args->children[1]->children[i]->token->type != SYMBOL_VALUE) { return NULL; }
    }

    // Prepare parameter list and code
    int numParams = args->children[1]->numChildren;
    char** params = malloc(numParams * sizeof(char**));
    for (int i = 0; i < numParams; ++i)
    {
        params[i] = args->children[1]->children[i]->token->symbol;
    }
    ParseTree* code = args->children[2];

    return value_create_lambda(environment, numParams, params, code);
}


Value* function_let (Environment* environment, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren != 3) { return NULL; }
    ParseTree* vars = args->children[1];
    ParseTree* code = args->children[2];

    // Check bindings
    if (vars->token != NULL) { return NULL; }
    for (int i = 0; i < vars->numChildren; ++i)
    {
        if (vars->children[i]->token != NULL) { return NULL; }
        ParseTree* var = vars->children[i]->children[0];
        ParseTree* val = vars->children[i]->children[1];
        if (var->token == NULL) { return NULL; }
        if (var->token->type != SYMBOL_VALUE) { return NULL; }
    }

    // Create environment from bindings
    Environment* env = environment_create(environment);
    for (int i = 0; i < vars->numChildren; ++i)
    {
        char* var = vars->children[i]->children[0]->token->symbol;
        ParseTree* val = vars->children[i]->children[1];
        Value* value = evaluate(val, environment);
        if (value == NULL) { environment_release(env); return NULL; }
        environment_set(env, var, value);
        value_release(value);
    }

    // Evaluate and return inner expression
    Value* value = evaluate(code, env);
    environment_release(env);
    return value;
}


Value* function_letrec (Environment* environment, ParseTree* args)
{
    return NULL; // Placeholder
}


Value* function_load (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren != 2) { return NULL; }
    if (args->children[1]->token->type != STRING_VALUE) { return NULL; }

    int f = open(args->children[1]->token->string, O_RDONLY);
    if (f == -1) { return NULL; }

    struct stat statbuf;
    if (fstat(f, &statbuf) == -1) { return NULL; }

    char* file = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, f, 0);
    if (file == MAP_FAILED) { return NULL; }
    close(f);

    StringBuffer* fileContents = strbuf_create();
    for (int i = 0; i<statbuf.st_size; ++i)
    {
        strbuf_append(fileContents, file[i]);
    }

    Environment* topEnvironment = environment;
    while (topEnvironment->parent != NULL)
    {
        topEnvironment = topEnvironment->parent;
    }
    Quack* expressions = parse(strbuf_data(fileContents));
    while (!quack_empty(expressions))
    {
        ParseTree* expression = quack_pop_front(expressions);
        Value* value = evaluate(expression, environment);
        if (value == NULL) { return NULL; }
        value_print(value);
        printf("\n");
        value_release(value);
        parsetree_release(expression);
    }

    strbuf_free(fileContents);
    quack_free(expressions);

    munmap(file, statbuf.st_size);

    return value_create(NULL_VALUE);   
}


Value* function_quote (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren != 2) { return NULL; }
    if (args->children[1]->token != NULL) { return NULL; }

    // Evaluate and return directly if we get a list back
    Value* value = evaluate_list(args->children[1]);
    if (value == NULL) { return NULL; }
    if (value->type == LIST_VALUE) { return value; }
    
    // Otherwise wrap returned primitive in a list and return
    Value* list = value_create(LIST_VALUE);
    list->head = value;
    list->tail = value_create_list_empty();
    return list;
}

