#ifndef PARSERTESTS_H
#define PARSERTESTS_H

#include "Parser/Parser.h"
#include "Tokenizer/Tokenizer.h"
#include "TestUtil.h"
#include "TokenUtil.h"


void test_parser_primitives ()
{
    start_test("Parser - Primitives");
    Quack* trees = parse("123 #f 9001");

    ParseTree* tree1 = quack_pop_front(trees);
    check_int(tree1->token, 123);
    parsetree_free(tree1);

    ParseTree* tree2 = quack_pop_front(trees);
    check_bool(tree2->token, false);
    parsetree_free(tree2);

    ParseTree* tree3 = quack_pop_front(trees);
    check_int(tree3->token, 9001);
    parsetree_free(tree3);

    assert(quack_empty(trees));
    quack_free(trees);
}


void test_parser_parens ()
{
    start_test("Parser - Parentheses");
    Quack* trees = parse("(a (5 6) [1.0 (#f) b])");
    ParseTree* tree = quack_pop_front(trees);

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
    assert(quack_empty(trees));
    quack_free(trees);
}


void test_parser ()
{
    test_parser_primitives();
    test_parser_parens();
}


#endif