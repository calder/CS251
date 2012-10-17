#ifndef SETTESTS_H
#define SETTESTS_H

#include <assert.h>
#include <stdio.h>
#include "Util/Set.h"
#include "TestUtil.h"


void test_set_create ()
{
	start_test("Set - Creation");

	Set* set = set_create();

	for (int i = 0; i < 20; ++i)
	{
		assert(set->array[i] == NULL);
	}
	assert(set->size == 0);

    set_free(set);
}

void test_set_add ()
{
    start_test("Set - Adding/Contains");

    Set* set = set_create();

    set_add(set, (void*)3);

    SetNode* addedNode = set->array[1];
    assert(addedNode->data == (void*)3);
    assert(addedNode->next == NULL);
    assert(set_contains(set, (void*)3));
    assert(set->size == 1);

    set_add(set, (void*)4);

    addedNode = ((SetNode*)set->array[1])->next;
    assert(addedNode->data == (void*)4);
    assert(addedNode->next == NULL);
    assert(set_contains(set, (void*)4));
    assert(set->size == 2);

    set_free(set);
}

void test_set_remove ()
{
    start_test("Set - Removal");

    Set* set = set_create();

    set_add(set, (void*)1);
    set_add(set, (void*)2);
    set_add(set, (void*)3);

    assert(set_contains(set, (void*)1));
    assert(set_contains(set, (void*)2));
    assert(set_contains(set, (void*)3));
    assert(set->size == 3);

    set_remove(set, (void*)2);
    assert(!set_contains(set, (void*)2));
    assert(set_contains(set, (void*)1));
    assert(set_contains(set, (void*)3));
    assert(set->size == 2);

    set_free(set);
}

void test_set_clear ()
{
    start_test("Set - Clearing");

    Set* set = set_create();

    set_add(set, (void*)1);
    set_add(set, (void*)2);
    set_add(set, (void*)3);

    set_clear(set);

    assert(!set_contains(set, (void*)1));
    assert(!set_contains(set, (void*)2));
    assert(!set_contains(set, (void*)3));
    assert(set->size == 0);

    set_free(set);
}

void test_set_print ()
{
    start_test("Set - Print");

    Set* set = set_create();

    set_add(set, (void*)1);
    set_add(set, (void*)2);
    set_add(set, (void*)3);
    set_print(set);
}

void test_set ()
{
	test_set_create();
	test_set_add();
    test_set_remove();
    test_set_clear();
    //test_set_print();
}

#endif