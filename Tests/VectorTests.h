#ifndef VECTORTESTS_H
#define VECTORTESTS_H

#include "Util/Vector.h"
#include "TestUtil.h"


void test_vector_append ()
{
    start_test("Vector - Append");
    Vector* vector = vector_create(vector);

    for (int i = 0; i < 64; ++i) { vector_append(vector, (void*)i); }
    for (int i = 0; i < 64; ++i) { assert(vector_get(vector, i) == (void*)i); }

    vector_free(vector);
}


void test_vector_set ()
{
    start_test("Vector - Set");
    Vector* vector = vector_create(vector);

    for (int i = 0; i < 64; ++i) { vector_append(vector, (void*)i); }
    for (int i = 0; i < 64; ++i) { vector_set(vector, i, (void*)(64 - i)); }
    for (int i = 0; i < 64; ++i) { assert(vector_get(vector, i) == (void*)(64 - i)); }

    vector_free(vector);
}


void test_vector ()
{
    test_vector_append();
    test_vector_set();
}


#endif