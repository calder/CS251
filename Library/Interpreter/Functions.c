#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Interpreter/Interpreter.h"
#include "Interpreter/Functions.h"
#include "Parser/Parser.h"
#include "Util/StringBuffer.h"


bool check_let_args (ParseTree* args);


Value* function_append (Environment* environment, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren < 2) { return NULL; }
    Value* listToAppend = evaluate(args->children[1], environment);
    if (listToAppend == NULL || listToAppend->type != LIST_VALUE) { value_release(listToAppend); return NULL; }
    Value* listPointer = listToAppend;
    for (int i = 2; i < args->numChildren; ++i)
    {
        Value* item = evaluate(args->children[i], environment);
        if (item == NULL) { value_release(listToAppend); value_release(item); return NULL; }
        while(listPointer-> tail != NULL && listPointer->tail->tail != NULL)
        { 
            listPointer = listPointer->tail; 
            if (listPointer->type != LIST_VALUE) { value_release(listToAppend); value_release(item); return NULL; }
        }
        value_release(listPointer->tail);
        listPointer->tail = item;
    }
    return listToAppend;
}


Value* function_begin (Environment* environment, ParseTree* args)
{
    return NULL; // Placeholder
}


Value* function_car (Environment* environment, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren != 2) { return NULL; }
    Value* list = evaluate(args->children[1], environment);
    if (list == NULL) { return NULL; }
    if (list->type != LIST_VALUE) { value_release(list); return NULL; }

    Value* head = list->head;
    value_reserve(head);
    value_release(list);
    return head;
}


Value* function_cdr (Environment* environment, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren != 2) { return NULL; }
    Value* list = evaluate(args->children[1], environment);
    if (list == NULL) { return NULL; }
    if (list->type != LIST_VALUE) { value_release(list); return NULL; }

    Value* tail = list->tail;
    value_reserve(tail);
    value_release(list);
    return tail;
}


Value* function_cons (Environment* environment, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren != 3) { return NULL; }
    Value* item1 = evaluate(args->children[1], environment);
    if (item1 == NULL) { return NULL; }
    Value* item2 = evaluate(args->children[2], environment);
    if (item2 == NULL) { value_release(item1); return NULL; }

    return value_create_list(item1,item2);
}


Value* function_cond (Environment* environment, ParseTree* args)
{
    return NULL; // Placeholder
}


Value* function_define (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren != 3) { return NULL; }
    ParseTree* var = args->children[1];
    ParseTree* val = args->children[2];
    if (var->token == NULL || var->token->type != SYMBOL_VALUE) { return NULL; }

    // Evaluate value and store in variable
    Value* value = evaluate(val, environment);
    if (value == NULL) { return NULL; }
    environment_set(environment, var->token->symbol, value);
    value_release(value);

    return value_create(NULL_VALUE);
}


Value* function_divide (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren < 2) { return NULL; }

    // Multiplicative inverse case
    if (args->numChildren == 2)
    {
        Value* v = evaluate(args->children[1], environment);
        if (v == NULL) { return NULL; }
        if (v->type == INTEGER_VALUE && (v->intVal == 1 || v->intVal == -1))
            { value_release(v); return value_create_int(v->intVal); }
        else if (v->type == INTEGER_VALUE || v->type == FLOAT_VALUE)
            { value_release(v); return value_create_float(1.0 / v->intVal); }
        else
            { value_release(v); return NULL; }
    }

    // Actual quotient cases
    else
    {
        double quotient = 1;
        bool integer = true;
        for (int i = 1; i < args->numChildren; ++i)
        {
            // Evaluate and check argument
            Value* value = evaluate(args->children[i], environment);
            if (value == NULL) { parsetree_print(args->children[i]); return NULL; }
            if (value->type != FLOAT_VALUE && value->type != INTEGER_VALUE)
            {
                value_release(value);
                return NULL;
            }

            // Dividor case
            if (i == 1)
            {
                if (value->type == FLOAT_VALUE) { quotient = value->floatVal; integer = false; }
                else if (value->type == INTEGER_VALUE) { quotient = value->intVal; }
            }

            // Divisor case
            else
            {
                if (value->type == FLOAT_VALUE)
                {
                    quotient /= value->floatVal;
                    integer = false;
                }
                else if (value->type == INTEGER_VALUE)
                {
                    quotient /= value->intVal;
                    if ((int)quotient % value->intVal != 0) { integer = false; }
                }
            }
            value_release(value);
        }

        // Return quotient as the correct type
        if (integer) { return value_create_int(quotient); }
        else         { return value_create_float(quotient); }
    }
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
    if (args->numChildren < 3) { return NULL; }

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
        params[i] = strdup(args->children[1]->children[i]->token->symbol);
    }

    return value_create_lambda(environment, numParams, params, args);
}


Value* function_let (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (!check_let_args(args)) { return NULL; }
    ParseTree* vars = args->children[1];

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

    return evaluate_bodies(args, env);
}


Value* function_letrec (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (!check_let_args(args)) { return NULL; }
    ParseTree* vars = args->children[1];

    // Initialize environment with undefineds
    Environment* env = environment_create(environment);
    for (int i = 0; i < vars->numChildren; ++i)
    {
        Value* value = value_create(UNDEF_VALUE);
        environment_set(env, vars->children[i]->children[0]->token->symbol, value);
        value_release(value);
    }

    // Evaluate and store actual values
    for (int i = 0; i < vars->numChildren; ++i)
    {
        Value* value = evaluate(vars->children[i]->children[1], env);
        if (value == NULL) { environment_release(env); return NULL; }
        environment_set(env, vars->children[i]->children[0]->token->symbol, value);
        value_release(value);
    }

    return evaluate_bodies(args, env);
}


Value* function_letstar (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (!check_let_args(args)) { return NULL; }
    ParseTree* vars = args->children[1];

    // Create sequential environments from bindings
    Environment* env = environment_create(environment);
    for (int i = 0; i < vars->numChildren; ++i)
    {
        // Evaluate and store in current environment
        char* var = vars->children[i]->children[0]->token->symbol;
        ParseTree* val = vars->children[i]->children[1];
        Value* value = evaluate(val, env);
        if (value == NULL) { environment_release(env); return NULL; }
        environment_set(env, var, value);

        // Create fresh environment
        env = environment_create(env);
        environment_release(env->parent);
        value_release(value);
    }

    return evaluate_bodies(args, env);
}


Value* function_list (Environment* environment, ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren < 2) { return NULL; }
    Value* builtList = value_create_list_empty();
    for (int i = args->numChildren - 1; i > 0; --i)
    {
        Value* item = evaluate(args->children[i], environment);
        if (item == NULL) { return NULL; }
        Value* listTemp = value_create_list_empty();
        listTemp->head = item;
        listTemp->tail = builtList;
        builtList = listTemp;
    }
    return builtList;
}


Value* function_load (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren != 2) { return NULL; }
    if (args->children[1]->token->type != STRING_VALUE) { return NULL; }

    // Load file in top environment
    while (environment->parent != NULL) { environment = environment->parent; }
    load_file(environment, args->children[1]->token->string);
    return value_create(NULL_VALUE);
}


Value* function_minus (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren < 2) { return NULL; }

    // Sum everything up
    double sum = 0;
    bool integer = true;
    for (int i = 1; i < args->numChildren; ++i)
    {
        // Evaluate and check argument
        Value* value = evaluate(args->children[i], environment);
        if (value == NULL) { return NULL; }
        if (value->type != FLOAT_VALUE && value->type != INTEGER_VALUE)
        {
            value_release(value);
            return NULL;
        }

        // Add (or subtract) value from total
        double v;
        if (value->type == FLOAT_VALUE) { v = value->floatVal; integer = false; }
        else if (value->type == INTEGER_VALUE) { v = value->intVal; }
        if (i != 1 || args->numChildren == 2) { v *= -1; }
        sum += v;
        value_release(value);
    }

    // Return sum as the correct type
    if (integer) { return value_create_int(sum); }
    else         { return value_create_float(sum); }
}


Value* function_null (Environment* environment, ParseTree* args)
{
    // Check that there's only a single argument
    if (args->numChildren != 2) { return NULL; }

    // Evaluate argument and test for null-ness
    Value* value = evaluate(args->children[1], environment);
    if (value == NULL) { return NULL; }
    bool null = false;
    if (value->type == LIST_VALUE &&
        value->head == NULL &&
        value->tail == NULL)
        { null = true; }
    value_release(value);
    return value_create_bool(null);
}


Value* function_plus (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren < 2) { return NULL; }

    // Sum everything up
    double sum = 0;
    bool integer = true;
    for (int i = 1; i < args->numChildren; ++i)
    {
        // Evaluate and check argument
        Value* value = evaluate(args->children[i], environment);
        if (value == NULL) { return NULL; }
        if (value->type != FLOAT_VALUE && value->type != INTEGER_VALUE)
        {
            value_release(value);
            return NULL;
        }

        // Add value to total
        if (value->type == FLOAT_VALUE) { sum += value->floatVal; integer = false; }
        else if (value->type == INTEGER_VALUE) { sum += value->intVal; }
        value_release(value);
    }

    // Return sum as the correct type
    if (integer) { return value_create_int(sum); }
    else         { return value_create_float(sum); }
}


Value* function_quote (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren != 2) { return NULL; }

    // Evaluate and return
    Value* value = evaluate_list(args->children[1]);
    if (value == NULL) { return NULL; }
    return value;
}


Value* function_setbang (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren != 3) { return NULL; }
    ParseTree* var = args->children[1];
    ParseTree* val = args->children[2];
    if (var->token == NULL || var->token->type != SYMBOL_VALUE) { return NULL; }

    // Evaluate value and store in variable
    Value* value = evaluate(val, environment);
    if (value == NULL) { return NULL; }

    Environment* env = environment;
    Vector* envs = vector_create();
    while (env != NULL)
    {
        vector_append(envs, env);
        env = env->parent;
    }
    int index = vector_size(envs);
    while (index > 0)
    {
        env = vector_get(envs, --index);
        if (environment_get(env, var->token->symbol) != NULL)
        {
            environment_set(env, var->token->symbol, value);
            value_release(value);
            vector_free(envs);
            return value_create(NULL_VALUE);

        }
    }
    value_release(value);
    vector_free(envs);
    return NULL;

    // Find the broadest scope (environment) in which the variable is defined
    // Reset it in that environment
    // If it doesn't exist in any environment, error

    /*
    while (env != NULL)
    {
        if (environment_get(env, var->token->symbol) != NULL)
        {
            // Var exists in an environment, so reset it
            // If it's not just in the scope of the set!
            // environment_set(env, var->token->symbol, value);
            // Otherwise, environment_set(environment, ");

            environment_set(environment, var->token->symbol, value);
            value_release(value);
            return value_create(NULL_VALUE);
        }
        env = env->parent;
    }
    */
    value_release(value);
    return NULL;
}


Value* function_times (Environment* environment, ParseTree* args)
{
    // Check arguments
    if (args->numChildren < 2) { return NULL; }

    // Sum everything up
    double prod = 1;
    bool integer = true;
    for (int i = 1; i < args->numChildren; ++i)
    {
        // Evaluate and check argument
        Value* value = evaluate(args->children[i], environment);
        if (value == NULL) { return NULL; }
        if (value->type != FLOAT_VALUE && value->type != INTEGER_VALUE)
        {
            value_release(value);
            return NULL;
        }

        // Multiply value into total
        if (value->type == FLOAT_VALUE) { prod *= value->floatVal; integer = false; }
        else if (value->type == INTEGER_VALUE) { prod *= value->intVal; }
        value_release(value);
    }

    // Return product as the correct type
    if (integer) { return value_create_int(prod); }
    else         { return value_create_float(prod); }
}


bool check_let_args (ParseTree* args)
{
    // Check number of arguments
    if (args->numChildren < 3) { return false; }
    ParseTree* vars = args->children[1];

    // Check bindings
    if (vars->token != NULL) { return false; }
    for (int i = 0; i < vars->numChildren; ++i)
    {
        if (vars->children[i]->token != NULL) { return false; }
        ParseTree* var = vars->children[i]->children[0];
        ParseTree* val = vars->children[i]->children[1];
        if (var->token == NULL) { return false; }
        if (var->token->type != SYMBOL_VALUE) { return false; }
    }

    // Hooray!
    return true;
}