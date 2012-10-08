#ifndef QUACKTESTS_H
#define QUACKTESTS_H

#include "Quack.h"
#include "TestUtil.h"


void testQuackQueue ()
{
    startTest("Quack - Queue");
    Quack* quack = createQuack();

    pushBack(quack, (void*) 1);
    pushBack(quack, (void*) 2);
    pushBack(quack, (void*) 3);

    failIfDifferent(popFront(quack), (void*) 1);
    failIfDifferent(popFront(quack), (void*) 2);
    failIfDifferent(popFront(quack), (void*) 3);

    freeQuack(quack);
}


void testQuackStack ()
{
    startTest("Quack - Stack");
    Quack* quack = createQuack();

    pushFront(quack, (void*) 1);
    pushFront(quack, (void*) 2);
    pushFront(quack, (void*) 3);

    failIfDifferent(popFront(quack), (void*) 3);
    failIfDifferent(popFront(quack), (void*) 2);
    failIfDifferent(popFront(quack), (void*) 1);

    freeQuack(quack);
}


void testQuackResize ()
{
    startTest("Quack - Resize");
    Quack* quack = createQuack();

    for (int i = 0; i < 64; ++i)
    {
        pushFront(quack, (void*) -i);
        pushBack(quack, (void*) i);
    }

    for (int i = 63; i >= 0; --i)
    {
        failIfDifferent(popFront(quack), (void*) -i);
        failIfDifferent(popBack(quack), (void*) i);
    }

    freeQuack(quack);
}


void testQuack ()
{
    testQuackQueue();
    testQuackStack();
    testQuackResize();
}


#endif