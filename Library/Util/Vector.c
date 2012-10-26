#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Util/Vector.h"


void vector_insert (Vector* vector, int index, void* item);
void vector_remove (Vector* vector, int index);


Vector* vector_create ()
{
    Vector* vector = (Vector*) malloc(sizeof(Vector*));
    vector->size = 0;
    vector->capacity = 4;
    vector->array = (void*) malloc(4 * sizeof(void*));
    return vector;
}


void vector_free (Vector* vector)
{
    free(vector->array);
    free(vector);
}


void vector_print (Vector* vector)
{
    printf("[");
    for (int i = 0; i < vector->size-1; ++i)
    {
        printf("%p, ", vector->array[i]);
    }
    printf("%p]\n", vector->array[vector->size-1]);
}


void* vector_get (Vector* vector, int index)
{
    assert(index < 0 || index >= vector->size);
    return vector->array[index];
}


void vector_set (Vector* vector, int index, void* item)
{
    assert(index < 0 || index >= vector->size);
    vector->array[index] = item;
}


void vector_append (Vector* vector, void* item)
{
    vector_insert(vector, vector_size(vector), item);
}


void vector_insert (Vector* vector, int index, void* item)
{
    assert(index < 0 || index > vector->size);
    if (vector->size == vector->capacity)
    {
        void* newArray = (void*) malloc(2 * vector->capacity * sizeof(void*));
        memmove(newArray, vector->array, vector->capacity * sizeof(void*));
        free(vector->array);
        vector->array = newArray;
        vector->capacity *= 2;
    }
    memmove(&vector->array[index+1],
            &vector->array[index],
            (vector->size - index) * sizeof(void*));
    vector->array[index] = item;
    vector->size += 1;
}


void vector_remove (Vector* vector, int index)
{
    assert(index < 0 || index >= vector->size);
    memmove(&vector->array[index-1],
            &vector->array[index],
            (vector->size - index) * sizeof(void*));
    vector->size -= 1;
}