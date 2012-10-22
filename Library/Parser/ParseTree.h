#ifndef PARSETREE_H
#define PARSETREE_H

#include "Tokenizer/Tokens.h"


/// A parse tree (or subtree)
struct __ParseTree
{
    Token* token;
    struct __ParseTree** children;
    int numChildren;
}
typedef ParseTree;


ParseTree* parsetree_create (Token* token, int numChildren);
void parsetree_free (ParseTree* tree);


#endif