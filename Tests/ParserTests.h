#ifndef PARSERTESTS_H
#define PARSERTESTS_H

#include <stdio.h>
#include "Parser/Parser.h"
#include "Tokenizer/Tokenizer.h"
#include "TestUtil.h"


void test_parser_parens ()
{
    start_test("Parser - Parentheses");
    ParseTree* tree = parse(tokenize("(a (5 6) [1.0 (#f) b])"));

    parsetree_print(tree);
    printf("\n");

    parsetree_free(tree);
}


void test_parser_lonestring ()
{
	start_test("Parser - Unparenthesized String");
    ParseTree* tree = parse(tokenize("\"merp\""));

    parsetree_print(tree);
    printf("\n");

    parsetree_free(tree);
}

void test_parser ()
{
    test_parser_parens();
    test_parser_lonestring();
}


#endif