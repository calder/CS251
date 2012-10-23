#ifndef TOKENIZERTESTS_H
#define TOKENIZERTESTS_H

#include <string.h>
#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Tokens.h"
#include "Util/Quack.h"
#include "TestUtil.h"


void check_bool (Quack* tokens, bool value);
void check_float (Quack* tokens, float value);
void check_int (Quack* tokens, int value);
void check_paren (Quack* tokens, char value);
void check_string (Quack* tokens, char* value);
void check_symbol (Quack* tokens, char* value);


void test_tokenizer_primitives ()
{
    start_test("Tokenizer - Primitives");
    Quack* tokens = tokenize("123 .456 7.89 #t #f \"Hello!\" W0rld");

    check_int    (tokens, 123);
    check_float  (tokens, .456);
    check_float  (tokens, 7.89);
    check_bool   (tokens, true);
    check_bool   (tokens, false);
    check_string (tokens, "\"Hello!\"");
    check_symbol (tokens, "W0rld");

    assert(quack_empty(tokens));
    quack_free(tokens);
}


void test_tokenizer_parens ()
{
    start_test("Tokenizer - Parentheses");
    Quack* tokens = tokenize("[]()[a](b)[ ]( )");

    check_paren  (tokens, '[');
    check_paren  (tokens, ']');
    check_paren  (tokens, '(');
    check_paren  (tokens, ')');
    check_paren  (tokens, '[');
    check_symbol (tokens, "a");
    check_paren  (tokens, ']');
    check_paren  (tokens, '(');
    check_symbol (tokens, "b");
    check_paren  (tokens, ')');
    check_paren  (tokens, '[');
    check_paren  (tokens, ']');
    check_paren  (tokens, '(');
    check_paren  (tokens, ')');

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


void check_bool (Quack* tokens, bool value)
{
    Token* token = quack_pop_front(tokens);
    assert(token->type == BOOLEAN_TOKEN);
    assert(token->boolData == value);
    token_free(token);
}


void check_float (Quack* tokens, float value)
{
    Token* token = quack_pop_front(tokens);
    assert(token->type == FLOAT_TOKEN);
    assert(token->floatData == value);
    token_free(token);
}


void check_int (Quack* tokens, int value)
{
    Token* token = quack_pop_front(tokens);
    assert(token->type == INTEGER_TOKEN);
    assert(token->intData == value);
    token_free(token);
}


void check_paren (Quack* tokens, char value)
{
    Token* token = quack_pop_front(tokens);
    assert(token->type == PAREN_TOKEN);
    assert(token->parenData == value);
    token_free(token);
}


void check_string (Quack* tokens, char* value)
{
    Token* token = quack_pop_front(tokens);
    assert(token->type == STRING_TOKEN);
    assert(!strcmp(token->stringData,value));
    token_free(token);
}


void check_symbol (Quack* tokens, char* value)
{
    Token* token = quack_pop_front(tokens);
    assert(token->type == SYMBOL_TOKEN);
    assert(!strcmp(token->symbolData,value));
    token_free(token);
}


#endif