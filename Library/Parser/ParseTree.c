#include <stdlib.h>
#include "Parser/ParseTree.h"


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
    free(tree->children);
    free(tree->token);
    free(tree);
}