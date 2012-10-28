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
    return NULL; // Placeholder
}


Value* function_quote (Closure* closure, ParseTree* args)
{
    if (args->numChildren != 2) { return NULL; }
    return value_create_expression(args->children[1]);
}