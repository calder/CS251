#include <stdlib.h>
#include <stdio.h>
#include "Parser/ParseTree.h"
#include "Tokenizer/Tokens.h"


ParseTree* parsetree_create (Token* token, int numChildren)
{
    ParseTree* tree = malloc(sizeof(ParseTree));
    tree->token = token;
    tree->children = malloc(sizeof(ParseTree) * numChildren);
    tree->numChildren = numChildren;
    return tree;
}


void parsetree_free (ParseTree* tree)
{
    // FREE THE CHILDREN!
    free(tree->children);
    free(tree->token);
    free(tree);
}

void parsetree_print (ParseTree* tree)
{
    if (tree->token != NULL)
    {
        token_print_parser(tree->token);
    }
    else
    {
        printf("( ");
        for (int i = 0; i < tree->numChildren; ++i)
        {
            parsetree_print(tree->children[i]);
        }
        printf(") ");
    }
}