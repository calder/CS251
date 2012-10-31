#ifndef INTERPRETERTESTS_H
#define INTERPRETERTESTS_H

#include <string.h>
#include "Interpreter/Interpreter.h"
#include "TestUtil.h"
#include "ValueUtil.h"


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
    assert(quack_empty(values));
    check_int_value(value, 456);
    value_release(value);

    quack_free(values);
}


void test_interpreter_quote ()
{
    start_test("Interpreter - Quote");
    Quack* values = interpret("(quote (123 () hello))");
    assert(!quack_empty(values));
    Value* list = quack_pop_front(values);
    assert(quack_empty(values));

    Value* box1 = list;
    check_list_value(box1);
    check_int_value(box1->listVal.head, 123);

    Value* box2 = box1->listVal.tail;
    check_list_value(box2);
    check_list_value(box2->listVal.head);
    assert(box2->listVal.head->listVal.head == NULL);
    assert(box2->listVal.head->listVal.tail == NULL);

    Value* box3 = box2->listVal.tail;
    check_list_value(box3);
    check_symbol_value(box3->listVal.head, "hello");

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