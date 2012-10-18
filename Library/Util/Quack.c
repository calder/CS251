#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Util/Quack.h"


Quack* quack_create ()
{
    Quack* quack = (Quack*) malloc(sizeof(Quack));
    quack->size = 0;
    quack->capacity = 4;
    quack->start = 0;
    quack->array = (void*) malloc(quack->capacity * sizeof(void*));
    return quack;
}


void quack_free (Quack* quack)
{
    free(quack->array);
    free(quack);
}


int quack_mem_index (Quack* quack, int index)
{
    if (index < 0) { index += quack->size; }
    return (quack->start + index + quack->capacity) % quack->capacity;
}


void* quack_get (Quack* quack, int index)
{
    return quack->array[quack_mem_index(quack,index)];
}


void quack_set (Quack* quack, int index, void* item)
{
    quack->array[quack_mem_index(quack,index)] = item;
}


void quack_debug_print (Quack* quack)
{
    printf("[");
    for (int i = 0; i < quack->capacity-1; ++i)
    {
        printf("%p ", quack->array[i]);
    }
    printf("%p] %d %d\n", quack->array[quack->capacity-1], quack->start, quack->size);
}


void quack_print (Quack* quack)
{
    printf("[");
    for (int i = 0; i < quack->size - 1; ++i)
    {
        printf("%p ", quack_get(quack, i));
    }
    if (quack->size > 0) { printf("%p", quack_get(quack, -1)); }
    printf("]\n");
}


bool quack_empty (Quack* quack)
{
    return quack->size == 0;
}


void quack_resize (Quack* quack, int newCapacity)
{
    assert(newCapacity > 0);
    void** newArray = (void**) malloc(newCapacity * sizeof(void*));
    if (quack->start + quack->size > quack->capacity)
    {
        // Copy first half, ie [   01234]
        int length1 = quack->capacity - quack->start;
        memmove(newArray,
                &quack->array[quack->start],
                length1 * sizeof(void*));

        // Copy second half, ie [567     ]
        int length2 = quack->size - length1;
        memmove(&newArray[length1],
                quack->array,
                length2 * sizeof(void*));
    }
    else
    {
        // The array doesn't wrap so we can copy normally
        memmove(newArray,
                &quack->array[quack->start],
                quack->size * sizeof(void*));
    }
    free(quack->array);
    quack->array = newArray;
    quack->capacity = newCapacity;
    quack->start = 0;
}


void quack_grow_if_full (Quack* quack)
{
    if (quack->size == quack->capacity)
    {
        quack_resize(quack, quack->size * 2);
    }
}


void quack_shrink_if_sparse (Quack* quack)
{
    if (quack->size > 0 && quack->size < quack->capacity / 4)
    { 
        quack_resize(quack, quack->capacity / 2);
    }
}


void quack_push_front (Quack* quack, void* item)
{
    quack_grow_if_full(quack);
    quack->start = (quack->start - 1 + quack->capacity) % quack->capacity;
    quack->size += 1;
    quack_set(quack, 0, item);
}


void quack_push_back (Quack* quack, void* item)
{
    quack_grow_if_full(quack);
    quack->size += 1;
    quack_set(quack, -1, item);
}


void* quack_pop_front (Quack* quack)
{
    assert(quack->size > 0);
    void* popped = quack_get(quack, 0);
    quack->start = quack_mem_index(quack, 1);
    quack->size -= 1;
    quack_shrink_if_sparse(quack);
    return popped;
}


void* quack_pop_back (Quack* quack)
{
    assert(quack->size > 0);
    void* popped = quack_get(quack, -1);
    quack->size -= 1;
    quack_shrink_if_sparse(quack);
    return popped;
}


void* quack_front (Quack* quack)
{
    assert(quack->size > 0);
    return quack_get(quack, 0);
}


void* quack_back (Quack* quack)
{
    assert(quack->size > 0);
    return quack_get(quack, -1);
}