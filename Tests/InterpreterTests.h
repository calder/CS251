#ifndef INTERPRETERTESTS_H
#define INTERPRETERTESTS_H

#include <string.h>
#include "Interpreter/Interpreter.h"
#include "TestUtil.h"
#include "ValueUtil.h"


void test_interpreter_append ()
{
    start_test("Interpreter - Append");
    Quack* values = interpret("(append (quote (5)) (quote (1)) (quote (2)))");
    assert(values != NULL && !quack_empty(values));

    Value* value = quack_pop_front(values);
    assert(value != NULL && value->type == LIST_VALUE);
    assert(value->head->type == INTEGER_VALUE && value->head->intVal == 5);
    assert(value->tail->head->type == INTEGER_VALUE && value->tail->head->intVal == 1);
    assert(value->tail->tail->head->type == INTEGER_VALUE && value->tail->tail->head->intVal == 2);
    assert(value->tail->tail->tail->head == NULL && value->tail->tail->tail->tail == NULL);

    quack_free(values);
    value_release(value);

    values = interpret("(append (quote (5)) 1)");
    assert(values != NULL && !quack_empty(values));
    value = quack_pop_front(values);
    assert(value != NULL && value->type == LIST_VALUE);
    assert(value->head->type == INTEGER_VALUE && value->head->intVal == 5);
    assert(value->tail->type == INTEGER_VALUE && value->tail->intVal == 1);
    quack_free(values);
    value_release(value);
}


void test_interpreter_car ()
{
    start_test("Interpreter - Car");
    Quack* values = interpret("(car (quote (1 2)))");
    assert(!quack_empty(values));

    Value* value = quack_pop_front(values);
    assert(value != NULL && value->type == INTEGER_VALUE);
    assert(value->intVal == 1);

    quack_free(values);
    value_release(value);
}


void test_interpreter_cdr ()
{
    start_test("Interpreter - Cdr");
    Quack* values = interpret("(cdr (quote (1 2)))");
    assert(!quack_empty(values));

    Value* value = quack_pop_front(values);
    assert(value != NULL && value->type == LIST_VALUE);
    assert(value->head->type == INTEGER_VALUE && value->head->intVal == 2);

    quack_free(values);
    value_release(value);
}


void test_interpreter_cons ()
{
    start_test("Interpreter - Cons");
    Quack* values = interpret("(cons 5 (quote (1 2)))");
    assert(values != NULL && !quack_empty(values));

    Value* value = quack_pop_front(values);
    assert(value != NULL && value->type == LIST_VALUE);
    assert(value->head->type == INTEGER_VALUE && value->head->intVal == 5);
    assert(value->tail->head->type == INTEGER_VALUE && value->tail->head->intVal == 1);

    quack_free(values);
    value_release(value);
}


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


void test_interpreter_divide ()
{
    start_test("Interpreter - Divide");
    Quack* values = interpret("(/ 500 5 10) (/ (/ 2) 5)");
    assert(!quack_empty(values));
    Value* value;

    value = quack_pop_front(values);
    check_int(value, 10);
    value_release(value);

    value = quack_pop_front(values);
    check_float(value, 0.1);
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


void test_interpreter_lessthan ()
{
    start_test("Interpreter - Lessthen");
    Quack* values = interpret("(< 3 2) (< 2 5) (< 2 3 4) (< 2 4 3)");
    assert(!quack_empty(values));

    Value* value = quack_pop_front(values);
    check_bool(value, false);
    value_release(value);

    value = quack_pop_front(values);
    check_bool(value, true);
    value_release(value);

    value = quack_pop_front(values);
    check_bool(value, true);
    value_release(value);

    value = quack_pop_front(values);
    check_bool(value, false);
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


void test_interpreter_list ()
{
    start_test("Interpreter - List");
    Quack* values = interpret("(list 5 1 2)");
    assert(values != NULL && !quack_empty(values));

    Value* value = quack_pop_front(values);
    assert(value != NULL && value->type == LIST_VALUE);
    assert(value->head->type == INTEGER_VALUE && value->head->intVal == 5);
    assert(value->tail->head->type == INTEGER_VALUE && value->tail->head->intVal == 1);
    assert(value->tail->tail->head->type == INTEGER_VALUE && value->tail->tail->head->intVal == 2);
    assert(value->tail->tail->tail->head == NULL && value->tail->tail->tail->tail == NULL);

    quack_free(values);
    value_release(value);
}


void test_interpreter_load ()
{
    start_test("Interpreter - Load");
    Quack* values = interpret("(lambda () 5) (load \"../Tests/LoadTest.rkt\")");
    assert(!quack_empty(values));
    Value* value;

    value = quack_pop_front(values);
    assert(value != NULL && value->type == LAMBDA_VALUE);
    Environment* environment = value->environment;
    check_int(environment_get(environment, "x"), 9001);
    value_release(value);

    value = quack_pop_front(values);
    assert(value != NULL && value->type == NULL_VALUE);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
}


void test_interpreter_minus ()
{
    start_test("Interpreter - Minus");
    Quack* values = interpret("(- 500 40 3) (- (- 0.14) 3)");
    assert(!quack_empty(values));
    Value* value;

    value = quack_pop_front(values);
    check_int(value, 457);
    value_release(value);

    value = quack_pop_front(values);
    check_float(value, -3.14);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
}


void test_interpreter_null ()
{
    start_test("Interpreter - Null?");
    Quack* values = interpret("(null? (quote ())) (null? (quote (())))");
    assert(!quack_empty(values));
    Value* value;

    value = quack_pop_front(values);
    check_bool(value,true);
    value_release(value);

    value = quack_pop_front(values);
    check_bool(value,false);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
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


void test_interpreter_times ()
{
    start_test("Interpreter - Times");
    Quack* values = interpret("(* 4 6 4) (* (* 1.5) 4)");
    assert(!quack_empty(values));
    Value* value;

    value = quack_pop_front(values);
    check_int(value, 96);
    value_release(value);

    value = quack_pop_front(values);
    check_float(value, 6.0);
    value_release(value);

    assert(quack_empty(values));
    quack_free(values);
}


void test_interpreter ()
{
    test_interpreter_append();
    test_interpreter_car();
    test_interpreter_cdr();
    test_interpreter_cons();
    test_interpreter_define();
    test_interpreter_divide();
    test_interpreter_if();
    test_interpreter_lambda();
    test_interpreter_lessthan();
    test_interpreter_let();
    test_interpreter_letrec();
    test_interpreter_list();
    test_interpreter_load();
    test_interpreter_minus();
    test_interpreter_null();
    test_interpreter_plus();
    test_interpreter_quote();
    test_interpreter_times();
}


#endif