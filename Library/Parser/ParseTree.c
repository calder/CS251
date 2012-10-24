#include <stdlib.h>
#include <stdio.h>
#include "Parser/ParseTree.h"
#include "Tokenizer/Tokens.h"


void parsetree_print_internal (ParseTree* tree);


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
    for (int i = 0; i < tree->numChildren; ++i)
    {
        parsetree_free(tree->children[i]);
    }
    free(tree->children);
    if (tree->token != NULL) { token_free(tree->token); }
    free(tree);
}


void parsetree_print (ParseTree* tree)
{
    parsetree_print_internal(tree);
    printf("\n");
}


void parsetree_print_internal (ParseTree* tree)
{
    if (tree->token != NULL) { token_print(tree->token); }
    else
    {
        printf("( ");
        for (int i = 0; i < tree->numChildren; ++i)
        {
            parsetree_print_internal(tree->children[i]);
        }
        printf(") ");
    }
}