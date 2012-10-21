#include <stdlib.h>
#include "Util/ParseTree.h"


ParseTree* parsetree_create (Token* token, int numChildren)
{
    ParseTree* tree = malloc(sizeof(ParseTree));
    tree->token = token;
    tree->children = malloc(sizeof(ParseTree) * numChildren);
    tree->size = 0;
    return tree;
}


void parsetree_free (ParseTree*)
{
    free(tree->children);
    free(tree->token);
    free(tree);
}