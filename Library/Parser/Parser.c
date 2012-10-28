#include <stdlib.h>
#include "Parser/Parser.h"
#include "Tokenizer/Tokenizer.h"
#include "Util/Quack.h"


ParseTree* make_parsetree_from_stack (Quack* parseStack);


Quack* parse (const char* input)
{
    Quack* parens = quack_create();
    Quack* tokens = quack_create();
    Quack* parseTrees = quack_create();

    bool success = parse_partial(input, parens, tokens, parseTrees);
    if (!success || !quack_empty(parens)) { goto syntax_error; }

    quack_free(parens);
    quack_free(tokens);
    return parseTrees;

syntax_error:
    
    quack_free(parens);
    quack_free(tokens);
    quack_free(parseTrees);
    return NULL;
}


bool parse_partial (const char* line, Quack* parens, Quack* tokens, Quack* parseTrees)
{
    // Tokenize the current line, then read through each token.  When you see an
    // open parentheses, push it to the paren stack.  When you see a close
    // parentheses, pop the last open off the paren stack and check that they
    // match.  After each token, check if the paren stack is empty and if it is
    // then ship it off for parsing.

    Quack* newTokens = tokenize(line);
    if (newTokens == NULL) { return false; }

    while (!quack_empty(newTokens))
    {
        Token* token = quack_pop_front(newTokens);
        quack_push_back(tokens, token);

        // Match parentheses
        if (token->type == PAREN_TOKEN)
        {
            // Open paren case
            if      (token->parenVal == '[') { quack_push_back(parens, "["); }
            else if (token->parenVal == '(') { quack_push_back(parens, "("); }

            // Close paren case
            else if (quack_empty(parens) ||
                    (token->parenVal - ((char*)quack_back(parens))[0] > 2))
                { goto syntax_error; }
            else { quack_pop_back(parens); }
        }

        // Parse expression if all parentheses match
        if (quack_empty(parens))
        {
            ParseTree* expression = parse_expression(tokens);
            if (expression == NULL) { goto syntax_error; }
            quack_push_back(parseTrees, expression);
        }
    }

    quack_free(newTokens);
    return true;

syntax_error:

    while (!quack_empty(newTokens))
    {
        token_free(quack_pop_front(newTokens));
    }
    quack_free(newTokens);
    return false;
}


ParseTree* parse_expression (Quack* tokens)
{
    Quack* parseStack = quack_create();

    while (quack_size(tokens) > 0)
    {
        Token* curToken = quack_pop_front(tokens);
        if (curToken->type == PAREN_TOKEN &&
            (curToken->parenVal == ')' ||
             curToken->parenVal == ']'))
        {
            make_parsetree_from_stack(parseStack);
        }
        else
        {
            if (curToken->type == PAREN_TOKEN && (curToken->parenVal == '(' || curToken->parenVal == '['))
            {
                quack_push_front(parseStack, NULL);
            }
            else 
            {
                ParseTree* node = parsetree_create(curToken, 0);
                quack_push_front(parseStack, node);   
            }
        }
    }
    
    ParseTree* parseTree = quack_pop_front(parseStack);
    quack_free(parseStack);
    return parseTree;
}


ParseTree* make_parsetree_from_stack (Quack* parseStack)
{
    Quack* expressionStack = quack_create();

    // Pop down to and including the last open paren (represented by NULL)
    while (quack_front(parseStack) != NULL)
    {
        quack_push_front(expressionStack, quack_pop_front(parseStack));
    }
    quack_pop_front(parseStack);

    // Create the parse tree
    ParseTree* parseTree = parsetree_create(NULL, quack_size(expressionStack));
    for (int i = 0; !quack_empty(expressionStack); ++i)
    {
        parseTree->children[i] = quack_pop_front(expressionStack);
    }
    quack_push_front(parseStack, parseTree);

    quack_free(expressionStack);
    return parseTree;
}