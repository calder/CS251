#include <stdlib.h>
#include <stdio.h>
#include "Parser/ParseTree.h"
#include "Tokenizer/Value.h"


ParseTree* parsetree_create (Value* value, int numChildren)
{
    ParseTree* tree = malloc(sizeof(ParseTree));
    tree->refCount = 1;
    tree->token = value;
    tree->children = malloc(sizeof(ParseTree) * numChildren);
    tree->numChildren = numChildren;
    return tree;
}


void parsetree_free (ParseTree* tree)
{
    // FREE THE CHILDREN!
    for (int i = 0; i < tree->numChildren; ++i)
    {
        parsetree_release(tree->children[i]);
    }
    free(tree->children);
    if (tree->token != NULL) { value_release(tree->token); }
    free(tree);
}


void parsetree_reserve (ParseTree* tree)
{
    tree->refCount += 1;
}


void parsetree_release (ParseTree* tree)
{
    tree->refCount -= 1;
    if (tree->refCount <= 0) { parsetree_free(tree); }
}


void parsetree_print (ParseTree* tree)
{
    if (tree->token != NULL) { value_print(tree->token); }
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


void parsetree_print_debug (ParseTree* tree)
{
    parsetree_print(tree);
    printf("\n");
}