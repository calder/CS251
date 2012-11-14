#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Interpreter/Binding.h"
#include "Interpreter/Environment.h"
#include "Interpreter/Functions.h"


Environment* environment_create (Environment* parent)
{
    Environment* environment = malloc(sizeof(Environment));
    environment->refCount = 1;
    environment->parent = parent;
    if (parent != NULL) { environment_reserve(parent); }
    environment->bindings = vector_create();
    return environment;
}


void environment_free (Environment* environment)
{
    for (int i = 0; i < vector_size(environment->bindings); ++i)
    {
        binding_free(vector_get(environment->bindings, i));
    }
    vector_free(environment->bindings);
    if (environment->parent != NULL) { environment_release(environment->parent); }
    free(environment);
}


void environment_reserve (Environment* environment)
{
    environment->refCount += 1;
}


void environment_release (Environment* environment)
{
    environment->refCount -= 1;
    if (environment->refCount <= 0) { environment_free(environment); }
}


void environment_print (Environment* environment)
{
    for (int i = 0; i < vector_size(environment->bindings); ++i)
    {
        binding_print(vector_get(environment->bindings, i));
    }
    if (environment->parent == NULL) { printf("\n"); }
    else
    {
        printf(">> ");
        environment_print(environment->parent);
    }
}


Value* environment_get (Environment* environment, const char* symbol)
{
    for (int i = 0; i < vector_size(environment->bindings); ++i)
    {
        Binding* binding = vector_get(environment->bindings, i);
        if (!strcmp(symbol, binding->symbol))
        {
            return binding->value;
        }
    }
    if (environment->parent != NULL) { return environment_get(environment->parent, symbol); }
    return NULL;
}


void environment_set (Environment* environment, const char* symbol, Value* value)
{
    for (int i = 0; i < vector_size(environment->bindings); ++i)
    {
        Binding* binding = vector_get(environment->bindings, i);
        if (!strcmp(symbol, binding->symbol))
        {
            binding_set(binding, value);
            return;
        }
    }
    vector_append(environment->bindings, binding_create(symbol,value));
}


void environment_set_default (Environment* environment, const char* symbol, Value* value)
{
    environment_set(environment, symbol, value);
    value_release(value);
}


Environment* environment_create_default ()
{
    Environment* env = environment_create(NULL);

    // Keyword functions (not first-class objects)
    environment_set_default(env, "begin",   value_create_keyword(&function_begin));
    environment_set_default(env, "cond",    value_create_keyword(&function_cond));
    environment_set_default(env, "define",  value_create_keyword(&function_define));
    environment_set_default(env, "display", value_create_keyword(&function_display));
    environment_set_default(env, "if",      value_create_keyword(&function_if));
    environment_set_default(env, "lambda",  value_create_keyword(&function_lambda));
    environment_set_default(env, "let",     value_create_keyword(&function_let));
    environment_set_default(env, "letrec",  value_create_keyword(&function_letrec));
    environment_set_default(env, "let*",    value_create_keyword(&function_letstar));
    environment_set_default(env, "load",    value_create_keyword(&function_load));
    environment_set_default(env, "quote",   value_create_keyword(&function_quote));
    environment_set_default(env, "set!",    value_create_keyword(&function_setbang));

    // Real Amurican functions
    environment_set_default(env, "+",       value_create_function(&function_plus));
    environment_set_default(env, "-",       value_create_function(&function_minus));
    environment_set_default(env, "*",       value_create_function(&function_times));
    environment_set_default(env, "/",       value_create_function(&function_divide));
    environment_set_default(env, ">",       value_create_function(&function_greaterthan));
    environment_set_default(env, ">=",      value_create_function(&function_greaterthaneqto));
    environment_set_default(env, "<",       value_create_function(&function_lessthan));
    environment_set_default(env, "<=",      value_create_function(&function_lessthaneqto));
    environment_set_default(env, "=",       value_create_function(&function_numequals));
    environment_set_default(env, "append",  value_create_function(&function_append));
    environment_set_default(env, "and",     value_create_function(&function_and));
    environment_set_default(env, "car",     value_create_function(&function_car));
    environment_set_default(env, "cdr",     value_create_function(&function_cdr));
    environment_set_default(env, "cons",    value_create_function(&function_cons));
    environment_set_default(env, "list",    value_create_function(&function_list));
    environment_set_default(env, "or",      value_create_function(&function_or));
    environment_set_default(env, "null?",   value_create_function(&function_null));

    return env;
}