#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Interpreter/Binding.h"
#include "Interpreter/Environment.h"


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
    assert(environment->refCount == 0);
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
    assert(environment->refCount > 0);
    environment->refCount += 1;
}


void environment_release (Environment* environment)
{
    assert(environment->refCount > 0);
    environment->refCount -= 1;
    if (environment->refCount <= 0) { environment_free(environment); }
}


void environment_print (Environment* environment)
{
    for (int i = 0; i < vector_size(environment->bindings); ++i)
    {
        binding_print(vector_get(environment->bindings, i));
    }
    if (environment->parent != NULL)
    {
        printf(">> ");
        environment_print(environment->parent);
    }
}