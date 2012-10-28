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


Environment* environment_create_default ()
{
    Environment* env = environment_create(NULL);

    environment_set(env, "if",     value_create_function_builtin(env, &function_if));
    environment_set(env, "lambda", value_create_function_builtin(env, &function_lambda));
    environment_set(env, "quote",  value_create_function_builtin(env, &function_quote));

    return env;
}