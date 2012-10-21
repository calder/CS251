#include <stdio.h>
#include "Parser.h"

ParseTree* parse (Quack* tokens)
{
    ParseTree* parseTree;
    Quack* parseStack = quack_create();

    for (int i = 0; i < quack_size(tokens); i++)
    {
        Token* curToken = quack_pop_front(tokens);
        if (curToken->type == PAREN_TOKEN && curToken->parenData == ')')
        {
            Quack* newStack = quack_create();
            while (quack_front(parseStack) != NULL)
            {
                quack_push_front(newStack, quack_pop_front(parseStack));
            }
            // Pop the remaining null pointer from the Quack
            quack_pop_front(parseStack);

            parseTree = parsetree_create(NULL, quack_size(newStack));
            for (int j = 0; j < quack_size(newStack); j++)
            {
                parseTree->children[j] = quack_pop_front(newStack);
            }
            quack_push_front(parseStack, parseTree);
        }
        else
        {
            if (curToken->type == PAREN_TOKEN && curToken->parenData == '(')
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
    return parseTree;
}