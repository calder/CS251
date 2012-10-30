#ifndef INTERPRETERTESTS_H
#define INTERPRETERTESTS_H

#include <string.h>
#include "Interpreter/Interpreter.h"
#include "TestUtil.h"


void test_interpreter_if ()
{
    start_test("Interpreter - If");
    Quack* values = interpret("(if #t 123 456) (if #f 123 456)");
    Value* value;

    assert(!quack_empty(values));
    value = quack_pop_front(values);
    assert(value->type == INTEGER_VALUE);
    assert(value->intVal == 123);
    value_release(value);

    assert(!quack_empty(values));
    value = quack_pop_front(values);
    assert(value->type == INTEGER_VALUE);
    assert(value->intVal == 456);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
}


void test_interpreter_let ()
{
    start_test("Interpreter - Let");
    Quack* values = interpret("(let ((x 123) (y 456)) y)");

    assert(!quack_empty(values));
    Value* value = quack_pop_front(values);
    assert(value->type == INTEGER_VALUE);
    assert(value->intVal == 456);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
}


void test_interpreter_quote ()
{
    start_test("Interpreter - Quote");
    Quack* values = interpret("(quote (123 () hello))");
    assert(!quack_empty(values));

    Value* list = quack_pop_front(values);
    assert(list != NULL);
    assert(list->type == LIST_VALUE);
    assert(quack_empty(values));

    Value* box1 = list;
    assert(box1 != NULL);
    assert(box1->type == LIST_VALUE);
    Value* item1 = box1->listVal.head;
    assert(item1 != NULL);
    assert(item1->type == INTEGER_VALUE);
    assert(item1->intVal == 123);

    Value* box2 = box1->listVal.tail;
    assert(box2 != NULL);
    assert(box2->type == LIST_VALUE);
    Value* item2 = box2->listVal.head;
    assert(item2 != NULL);
    assert(item2->type == LIST_VALUE);
    assert(item2->listVal.head == NULL);
    assert(item2->listVal.tail == NULL);

    Value* box3 = box2->listVal.tail;
    assert(box3 != NULL);
    assert(box3->type == LIST_VALUE);
    Value* item3 = box3->listVal.head;
    assert(item3 != NULL);
    assert(item3->type == SYMBOL_VALUE);
    assert(!strcmp(item3->stringVal, "hello"));

    value_release(list);
    quack_free(values);
}


void test_interpreter ()
{
    test_interpreter_if();
    test_interpreter_let();
    test_interpreter_quote();
}


#endif