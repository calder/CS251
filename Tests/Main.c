#include "ParserTests.h"
#include "QuackTests.h"
#include "StringBufferTests.h"
#include "TestUtil.h"
#include "TokenizerTests.h"


int main (int argc, char** argv)
{
    start_testing();

    // Data structures and utilities
    test_quack();
    test_strbuf();

    // Tokenizer
    test_tokenizer();

    // Parser
    test_parser();

    finish_testing();
    return 0;
}