#include <stdio.h>
#include <stdlib.h>
#include "Parser/Parser.h"
#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Tokens.h"
#include "Util/StringBuffer.h"


int main (int argc, char** argv)
{
    // Read standard input character by character, appending to a buffer.  When
    // a newline is read, ship the line off to the tokenizer for tokenization.
    // Then read through each token, and whenever the net parentheses hit 0
    // parse the expression.

    char c = 7;
    StringBuffer* buf = strbuf_create();
    Quack* parens = quack_create();
    Quack* tokens = quack_create();
    Quack* expressions = quack_create();

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

    // Print each expression's parse tree
    while (!quack_empty(expressions))
    {
        ParseTree* expression = quack_pop_front(expressions);
        parsetree_print(expression);
        parsetree_release(expression);
    }

    strbuf_free(buf);
    quack_free(parens);
    quack_free(tokens);
    quack_free(expressions);
    return 0;

syntax_error:
    
    strbuf_free(buf);
    quack_free(parens);
    quack_free(tokens);
    quack_free(expressions);
    printf("Syntax Error!\n");
    return 1;
}