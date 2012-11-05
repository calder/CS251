#ifndef INTERPRETERTESTS_H
#define INTERPRETERTESTS_H

#include <string.h>
#include "Interpreter/Interpreter.h"
#include "TestUtil.h"
#include "ValueUtil.h"


void test_interpreter_define ()
{
    start_test("Interpreter - Define");
    Quack* values = interpret("(define x 321) (define x 654) x");
    assert(!quack_empty(values));
    Value* value;

    value = quack_pop_front(values);
    assert(value != NULL && value->type == NULL_VALUE);
    value_release(value);

    value = quack_pop_front(values);
    assert(value != NULL && value->type == NULL_VALUE);
    value_release(value);

    value = quack_pop_front(values);
    check_int(value, 654);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
}


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


void test_interpreter_lambda ()
{
    start_test("Interpreter - Lambda");
    Quack* values = interpret("(((lambda (x y) (lambda () x x y)) 123 456))");
    assert(!quack_empty(values));

    Value* value = quack_pop_front(values);
    check_int(value, 456);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
}


void test_interpreter_let ()
{
    start_test("Interpreter - Let");
    Quack* values = interpret("(let ((x 123) (y 456)) x x y)");
    assert(!quack_empty(values));

    Value* value = quack_pop_front(values);
    check_int(value, 456);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
}


void test_interpreter_letrec ()
{
    start_test("Interpreter - LetRec");
    Quack* values = interpret("(letrec ((f 456) (g (lambda () f))) (g))");
    assert(!quack_empty(values));

    Value* value = quack_pop_front(values);
    check_int(value,456);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
}


void test_interpreter_load ()
{
    start_test("Interpreter - Load");
    interpret("(load \"sample.rkt\")");
}


void test_interpreter_plus ()
{
    start_test("Interpreter - Plus");
    Quack* values = interpret("(+ 500 40 3) (+ (+ 0.14) 3)");
    assert(!quack_empty(values));
    Value* value;

    value = quack_pop_front(values);
    check_int(value, 543);
    value_release(value);

    value = quack_pop_front(values);
    check_float(value, 3.14);
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
    assert(quack_empty(values));

    Value* box1 = list;
    check_list(box1);
    check_int(box1->head, 123);

    Value* box2 = box1->tail;
    check_list(box2);
    check_list(box2->head);
    assert(box2->head->head == NULL);
    assert(box2->head->tail == NULL);

    Value* box3 = box2->tail;
    check_list(box3);
    check_symbol(box3->head, "hello");

    value_release(list);
    quack_free(values);
}


void test_interpreter ()
{
    test_interpreter_define();
    test_interpreter_if();
    test_interpreter_lambda();
    test_interpreter_let();
    test_interpreter_letrec();
    //test_interpreter_load();
    test_interpreter_plus();
    test_interpreter_quote();
}


#endif