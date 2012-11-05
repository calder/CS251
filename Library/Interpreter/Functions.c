#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Interpreter/Interpreter.h"
#include "Interpreter/Functions.h"
#include "Parser/Parser.h"
#include "Util/StringBuffer.h"


bool check_let_args (ParseTree* args);


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