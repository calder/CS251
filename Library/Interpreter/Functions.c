#include <stdlib.h>
#include "Interpreter/Interpreter.h"
#include "Interpreter/Functions.h"


Value* function_if (Closure* closure, ParseTree* args)
{
    if (args->numChildren != 4) { return NULL; }
    Value* condition = evaluate(args->children[1], closure->environment);
    if (condition == NULL) { return NULL; }
    if (condition->type != BOOLEAN_VALUE) { value_release(condition); return NULL; }

    bool cond = condition->boolVal;
    value_release(condition);
    if (cond) { return evaluate(args->children[2], closure->environment); }
    else      { return evaluate(args->children[3], closure->environment); }
}


Value* function_lambda (Closure* closure, ParseTree* args)
{
    if (args->numChildren != 3) { return NULL; }

    for (int i = 0; i < args->children[1]->numChildren; ++i)
    {
        if (args->children[1]->children[i]->token == NULL) { return NULL; }
        if (args->children[1]->children[i]->token->type != SYMBOL_TOKEN) { return NULL; }
    }

    Value* value = value_create(FUNCTION_VALUE);
    value->funcVal.function = &function_eval_lambda;
    value->funcVal.environment = closure->environment;
    value->funcVal.numParams = args->children[1]->numChildren;
    value->funcVal.params = malloc(value->funcVal.numParams * sizeof(char*));

    for (int i = 0; i < args->children[1]->numChildren; ++i)
    {
        value->funcVal.params[i] = args->children[1]->children[i]->token->symbolVal;
    }

    value->funcVal.parseTree = args->children[2];
    environment_reserve(value->funcVal.environment);
    parsetree_reserve(value->funcVal.parseTree);
    return value;
}


Value* function_quote (Closure* closure, ParseTree* args)
{
    if (args->numChildren != 2) { return NULL; }
    return value_create_expression(args->children[1]);
}