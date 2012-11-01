#ifndef TOKENIZERTESTS_H
#define TOKENIZERTESTS_H

#include "Tokenizer/Tokenizer.h"
#include "Util/Quack.h"
#include "ValueUtil.h"
#include "TestUtil.h"


void test_tokenizer_primitives ()
{
    start_test("Tokenizer - Primitives");
    Quack* tokens = tokenize("123 .456 7.89 #t #f \"Hello!\" W0rld");

    check_and_free_int    (quack_pop_front(tokens), 123);
    check_and_free_float  (quack_pop_front(tokens), .456);
    check_and_free_float  (quack_pop_front(tokens), 7.89);
    check_and_free_bool   (quack_pop_front(tokens), true);
    check_and_free_bool   (quack_pop_front(tokens), false);
    check_and_free_string (quack_pop_front(tokens), "Hello!");
    check_and_free_symbol (quack_pop_front(tokens), "W0rld");

    assert(quack_empty(tokens));
    quack_free(tokens);
}


void test_tokenizer_parens ()
{
    start_test("Tokenizer - Parentheses");
    Quack* tokens = tokenize("[]()[a](b)[ ]( )");

    check_and_free_paren  (quack_pop_front(tokens), '[');
    check_and_free_paren  (quack_pop_front(tokens), ']');
    check_and_free_paren  (quack_pop_front(tokens), '(');
    check_and_free_paren  (quack_pop_front(tokens), ')');
    check_and_free_paren  (quack_pop_front(tokens), '[');
    check_and_free_symbol (quack_pop_front(tokens), "a");
    check_and_free_paren  (quack_pop_front(tokens), ']');
    check_and_free_paren  (quack_pop_front(tokens), '(');
    check_and_free_symbol (quack_pop_front(tokens), "b");
    check_and_free_paren  (quack_pop_front(tokens), ')');
    check_and_free_paren  (quack_pop_front(tokens), '[');
    check_and_free_paren  (quack_pop_front(tokens), ']');
    check_and_free_paren  (quack_pop_front(tokens), '(');
    check_and_free_paren  (quack_pop_front(tokens), ')');

    assert(quack_empty(tokens));
    quack_free(tokens);
}


void test_tokenizer_error ()
{
    start_test("Tokenizer - Syntax Errors");

    assert(tokenize("\"") == NULL);
    assert(tokenize("\"\n\"") == NULL);
}


void test_tokenizer ()
{
    test_tokenizer_primitives();
    test_tokenizer_parens();
    test_tokenizer_error();
}


#endif