#ifndef PARSERTESTS_H
#define PARSERTESTS_H

#include "Parser/Parser.h"
#include "Tokenizer/Tokenizer.h"
#include "TestUtil.h"


void test_parser_parens ()
{
    start_test("Parser - Parentheses");
    ParseTree* tree = parse(tokenize("(a (5 #f) [1.0 (#f) b])"));

    parsetree_print(tree);

    parsetree_free(tree);
}


void test_parser ()
{
    test_parser_parens();
}


#endif