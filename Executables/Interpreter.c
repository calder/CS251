#include <stdio.h>
#include <stdlib.h>
#include "Interpreter/Interpreter.h"
#include "Parser/Parser.h"
#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Tokens.h"
#include "Util/StringBuffer.h"


int main (int argc, char** argv)
{
    char c = 7;
    StringBuffer* buf = strbuf_create();
    Quack* parens = quack_create();
    Quack* tokens = quack_create();
    Quack* expressions = quack_create();
    Environment* environment = environment_create_default();

    while (c != 0 && c != EOF)
    {
        c = getchar();
        strbuf_append(buf, c);
        if (c != '\n' && c != EOF) { continue; }

        // Tokenize line
        if (!parse_partial(strbuf_data(buf), parens, tokens, expressions))
            { goto syntax_error; }
        strbuf_clear(buf);
    }

    // Make sure input didn't end mid-expression
    if (!quack_empty(parens)) { goto syntax_error; }

    // Evaluate and print each expression
    while (!quack_empty(expressions))
    {
        ParseTree* expression = quack_pop_front(expressions);
        Value* value = evaluate(expression, environment);
        if (value == NULL) { goto syntax_error; }
        value_print(value);
        printf("\n");
        value_release(value);
    }

    strbuf_free(buf);
    quack_free(parens);
    quack_free(tokens);
    quack_free(expressions);
    environment_release(environment);
    return 0;

syntax_error:
    
    strbuf_free(buf);
    quack_free(parens);
    quack_free(tokens);
    quack_free(expressions);
    environment_release(environment);
    printf("Syntax Error!\n");
    return 1;
}