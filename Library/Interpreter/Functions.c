#include <stdlib.h>
#include "Interpreter/Interpreter.h"
#include "Interpreter/Functions.h"


Value* function_lambda_eval (Closure* closure, ParseTree* parseTree);


Value* function_if (Closure* closure, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren != 4) { return NULL; }

    // Evaluate and check condition
    Value* condition = evaluate(args->children[1], closure->environment);
    if (condition == NULL) { return NULL; }
    if (condition->type != BOOLEAN_VALUE) { value_release(condition); return NULL; }

    // Evaluate and return the right case
    bool cond = condition->boolVal;
    value_release(condition);
    if (cond) { return evaluate(args->children[2], closure->environment); }
    else      { return evaluate(args->children[3], closure->environment); }
}


Value* function_lambda (Closure* closure, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren != 3) { return NULL; }

    // Check lambda parameters
    for (int i = 0; i < args->children[1]->numChildren; ++i)
    {
        if (args->children[1]->children[i]->token == NULL) { return NULL; }
        if (args->children[1]->children[i]->token->type != SYMBOL_TOKEN) { return NULL; }
    }

    // Initialize everything but parameters
    Value* value = value_create(FUNCTION_VALUE);
    value->funcVal.function = &function_lambda_eval;
    value->funcVal.environment = closure->environment;
    value->funcVal.parseTree = args->children[2];
    environment_reserve(value->funcVal.environment);
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


Value* function_lambda_eval (Closure* closure, ParseTree* args)
{
    return NULL; // Placeholder
}


Value* function_let (Closure* closure, ParseTree* args)
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
    Environment* env = environment_create(closure->environment);
    for (int i = 0; i < vars->numChildren; ++i)
    {
        char* var = vars->children[i]->children[0]->token->symbolVal;
        ParseTree* val = vars->children[i]->children[1];
        Value* value = evaluate(val, closure->environment);
        if (value == NULL) { environment_release(env); return NULL; }
        environment_set(env, var, value);
        value_release(value);
    }

    // Evaluate and return inner expression
    Value* value = evaluate(code, env);
    environment_release(env);
    return value;
}


Value* function_quote (Closure* closure, ParseTree* args)
{
    if (args->numChildren != 2) { return NULL; }
    return value_create_expression(args->children[1]);
}