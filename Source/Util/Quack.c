#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Util/Quack.h"


Quack* createQuack ()
{
    Quack* quack = (Quack*) malloc(sizeof(Quack));
    quack->size = 0;
    quack->capacity = 4;
    quack->start = 0;
    quack->array = (void*) malloc(quack->capacity * sizeof(void*));
    return quack;
}


void freeQuack (Quack* quack)
{
    free(quack->array);
    free(quack);
}


void freeQuackAndContents (Quack* quack)
{
    while (!empty(quack)) { freeBack(quack); }
    freeQuack(quack);
}


int memIndex (Quack* quack, int index)
{
    if (index < 0) { index += quack->size; }
    return (quack->start + index + quack->capacity) % quack->capacity;
}


void* get (Quack* quack, int index)
{
    return quack->array[memIndex(quack,index)];
}


void set (Quack* quack, int index, void* item)
{
    quack->array[memIndex(quack,index)] = item;
}


void debugPrint (Quack* quack)
{
    printf("[");
    for (int i = 0; i < quack->capacity-1; ++i)
    {
        printf("%p ", quack->array[i]);
    }
    printf("%p] %d %d\n", quack->array[quack->capacity-1], quack->start, quack->size);
}


void print (Quack* quack)
{
    printf("[");
    for (int i = 0; i < quack->size - 1; ++i)
    {
        printf("%p ", get(quack, i));
    }
    if (quack->size > 0) { printf("%p", get(quack, -1)); }
    printf("]\n");
}


bool empty (Quack* quack)
{
    return quack->size == 0;
}


void resize (Quack* quack, int newCapacity)
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


void grow (Quack* quack)
{
    if (quack->size == quack->capacity)
    {
        resize(quack, quack->size * 2);
    }
}


void shrink (Quack* quack)
{
    if (quack->size > 0 && quack->size < quack->capacity / 4)
    { 
        resize(quack, quack->capacity / 2);
    }
}


void pushFront (Quack* quack, void* item)
{
    grow(quack);
    quack->start = (quack->start - 1 + quack->capacity) % quack->capacity;
    quack->size += 1;
    set(quack, 0, item);
}


void pushBack (Quack* quack, void* item)
{
    grow(quack);
    quack->size += 1;
    set(quack, -1, item);
}


void* popFront (Quack* quack)
{
    assert(quack->size > 0);
    void* popped = get(quack, 0);
    quack->start = memIndex(quack, 1);
    quack->size -= 1;
    shrink(quack);
    return popped;
}


void* popBack (Quack* quack)
{
    assert(quack->size > 0);
    void* popped = get(quack, -1);
    quack->size -= 1;
    shrink(quack);
    return popped;
}


void* front (Quack* quack)
{
    assert(quack->size > 0);
    return get(quack, 0);
}


void* back (Quack* quack)
{
    assert(quack->size > 0);
    return get(quack, -1);
}


void freeFront (Quack* quack)
{
    free(popFront(quack));
}


void freeBack (Quack* quack)
{
    free(popBack(quack));
}