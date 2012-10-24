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


/// Malloc and return an empty ParseTree
ParseTree* parsetree_create (Token* token, int numChildren);

/// Recursively free an entire ParseTree including all Tokens
void parsetree_free (ParseTree* tree);

/// Recursively print an entire ParseTree for debugging purposes
void parsetree_print (ParseTree * tree);


#endif