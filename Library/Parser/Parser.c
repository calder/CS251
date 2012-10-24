#include <stdio.h>
#include "Parser/Parser.h"
#include "Tokenizer/Tokens.h"


ParseTree* parse (Quack* tokens)
{
    ParseTree* parseTree;
    Quack* parseStack = quack_create();

    while (quack_size(tokens) > 0)
    {
        Token* curToken = quack_pop_front(tokens);
        if (curToken->type == PAREN_TOKEN && (curToken->parenData == ')' || curToken->parenData == ']'))
        {
            Quack* newStack = quack_create();
            while (quack_front(parseStack) != NULL)
            {
                quack_push_front(newStack, quack_pop_front(parseStack));
            }
            // Pop the remaining null pointer from the Quack
            quack_pop_front(parseStack);

            parseTree = parsetree_create(NULL, quack_size(newStack));
            int j = 0;
            while (quack_size(newStack) > 0)
            {
                parseTree->children[j++] = quack_pop_front(newStack);
            }
            quack_push_front(parseStack, parseTree);
        }
        else
        {
            if (curToken->type == PAREN_TOKEN && (curToken->parenData == '(' || curToken->parenData == '['))
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