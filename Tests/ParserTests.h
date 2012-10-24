#ifndef PARSERTESTS_H
#define PARSERTESTS_H

#include "Parser/Parser.h"
#include "Tokenizer/Tokenizer.h"
#include "TestUtil.h"
#include "TokenUtil.h"


void test_parser_primitive ()
{
    start_test("Parser - Primitive");
    ParseTree* tree = parse(tokenize("\"merp\""));

    parsetree_print(tree);

    parsetree_free(tree);
}


void test_parser_parens ()
{
    start_test("Parser - Parentheses");
    ParseTree* tree = parse(tokenize("(a (5 6) [1.0 (#f) b])"));

    assert       (tree->token == NULL);
    check_symbol (tree->children[0]->token, "a");
    assert       (tree->children[1]->token == NULL);
    check_int    (tree->children[1]->children[0]->token, 5);
    check_int    (tree->children[1]->children[1]->token, 6);
    assert       (tree->children[2]->token == NULL);
    check_float  (tree->children[2]->children[0]->token, 1.0);
    assert       (tree->children[2]->children[1]->token == NULL);
    check_bool   (tree->children[2]->children[1]->children[0]->token, false);
    check_symbol (tree->children[2]->children[2]->token, "b");

    parsetree_free(tree);
}


void test_parser_broken_parens ()
{
    start_test("Parser - Broken Parentheses");
    parsetree_print(parse(tokenize("(a (5 6) [1.0 (#f] b)")));
}


void test_parser ()
{
    // test_parser_primitive();
    test_parser_parens();
    test_parser_broken_parens();
}


#endif