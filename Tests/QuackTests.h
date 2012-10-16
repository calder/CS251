#ifndef QUACKTESTS_H
#define QUACKTESTS_H

#include <assert.h>
#include "Util/Quack.h"
#include "TestUtil.h"


void test_quack_queue ()
{
    start_test("Quack - Queue");
    Quack* quack = quack_create();

    quack_push_back(quack, (void*) 1);
    quack_push_back(quack, (void*) 2);
    quack_push_back(quack, (void*) 3);

    assert(quack_pop_front(quack) == (void*) 1);
    assert(quack_pop_front(quack) == (void*) 2);
    assert(quack_pop_front(quack) == (void*) 3);

    quack_free(quack);
}


void test_quack_stack ()
{
    start_test("Quack - Stack");
    Quack* quack = quack_create();

    quack_push_front(quack, (void*) 1);
    quack_push_front(quack, (void*) 2);
    quack_push_front(quack, (void*) 3);

    assert(quack_pop_front(quack) == (void*) 3);
    assert(quack_pop_front(quack) == (void*) 2);
    assert(quack_pop_front(quack) == (void*) 1);

    quack_free(quack);
}


void test_quack_resize ()
{
    start_test("Quack - Resize");
    Quack* quack = quack_create();

    for (int i = 0; i < 64; ++i)
    {
        quack_push_front(quack, (void*) -i);
        quack_push_back(quack, (void*) i);
    }

    for (int i = 63; i >= 0; --i)
    {
        assert(quack_pop_front(quack) == (void*) -i);
        assert(quack_pop_back(quack) == (void*) i);
    }

    quack_free(quack);
}


void test_quack ()
{
    test_quack_queue();
    test_quack_stack();
    test_quack_resize();
}


#endif