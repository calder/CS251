#include "EnvironmentTests.h"
#include "InterpreterTests.h"
#include "ParserTests.h"
#include "QuackTests.h"
#include "StringBufferTests.h"
#include "TokenizerTests.h"
#include "VectorTests.h"


int main (int argc, char** argv)
{
    start_testing();

    // Data structures and utilities
    test_quack();
    test_strbuf();
    test_vector();

    // Tokenizer
    test_tokenizer();

    // Parser
    test_parser();

    // Interpreter
    test_environment();
    test_interpreter();

    finish_testing();
    return 0;
}