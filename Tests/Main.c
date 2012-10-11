#include <stdio.h>

#include "QuackTests.h"
#include "SetTests.h"
#include "VectorTests.h"
#include "TestUtil.h"
#include "TokenizerTests.h"


int main (int argc, char** argv)
{
    start_testing();

    // Data structures and utilities
    test_quack();
    test_set();
    test_vector();

    // Tokenizer
    test_tokenizer();

    // Parser

    finish_testing();
    return 0;
}