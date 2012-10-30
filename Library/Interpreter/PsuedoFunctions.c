#include <stdlib.h>
#include "Interpreter/Interpreter.h"
#include "Interpreter/PsuedoFunctions.h"


Value* function_lambda_eval (Closure* closure, ParseTree* parseTree);


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
        if (args->children[1]->children[i]->token->type != SYMBOL_TOKEN) { return NULL; }
    }

    // Initialize everything but parameters
    Value* value = value_create_function(environment, &function_lambda_eval);
    value->funcVal.parseTree = args->children[2];
    parsetree_reserve(value->funcVal.parseTree);

    // Initialize parameter list
    value->funcVal.numParams = args->children[1]->numChildren;
    value->funcVal.params = malloc(value->funcVal.numParams * sizeof(char*));
    for (int i = 0; i < args->children[1]->numChildren; ++i)
    {
        value->funcVal.params[i] = args->children[1]->children[i]->token->symbolVal;
    }

    return value;
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
        if (var->token->type != SYMBOL_TOKEN) { return NULL; }
    }

    // Create environment from bindings
    Environment* env = environment_create(environment);
    for (int i = 0; i < vars->numChildren; ++i)
    {
        char* var = vars->children[i]->children[0]->token->symbolVal;
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
    list->listVal.head = value;
    list->listVal.tail = value_create_list_empty();
    return list;
}