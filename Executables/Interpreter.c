#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Interpreter/Interpreter.h"
#include "Parser/Parser.h"
#include "Tokenizer/Value.h"
#include "Util/StringBuffer.h"


void load_libraries (Environment* environment, int argc, char** argv);


int main (int argc, char** argv)
{
    char c = 7;
    StringBuffer* buf = strbuf_create();
    Quack* parens = quack_create();
    Quack* tokens = quack_create();
    Quack* expressions = quack_create();
    Environment* environment = environment_create_default();
    load_libraries(environment, argc, argv);
    if (isatty(0)) { printf("Welcome to The Inderpreter!  Press ^D to exit.\n>>> "); }

    while (c != 0 && c != EOF)
    {
        // Check for line end
        c = getchar();
        strbuf_append(buf, c);
        if (c != '\n' && c != EOF) { continue; }

        // Parse line
        if (!parse_partial(strbuf_data(buf), parens, tokens, expressions))
        {
            printf("Syntax Error\n");
            if (isatty(0)) { printf(">>> "); }
            strbuf_clear(buf);
            continue;
        }
        strbuf_clear(buf);

        // Evaluate and print each expression
        while (!quack_empty(expressions))
        {
            ParseTree* expression = quack_pop_front(expressions);
            Value* value = evaluate(expression, environment);
            if (value == NULL) { printf("Runtime Error\n"); continue; }
            if (value->type != NULL_VALUE) { value_print(value); printf("\n"); }
            value_release(value);
            parsetree_release(expression);
        }
        if (isatty(0) && c != EOF)
        {
            if (quack_empty(parens)) { printf(">>> "); }
            else                     { printf("... "); }
        }
    }
    if (isatty(0)) { printf("\n"); }

    // Make sure file input didn't end mid-expression
    if (!isatty(0) && !quack_empty(parens)) { printf("Syntax Error\n"); }

    strbuf_free(buf);
    quack_free(parens);
    quack_free(tokens);
    quack_free(expressions);
    environment_release(environment);
    return 0;
}


void load_libraries (Environment* environment, int argc, char** argv)
{
    for (int i = 1; i < argc; ++i)
    {
        if (!load_file(environment, argv[i]))
        {
            printf("Error loading library %s\n", argv[i]);
        }
    }
}