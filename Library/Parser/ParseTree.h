#ifndef PARSETREE_H
#define PARSETREE_H

#include "Tokenizer/Tokens.h"


/// A parse tree (or subtree)
struct ParseTree
{
    int refCount;
    Token* token;
    struct ParseTree** children;
    int numChildren;
}
typedef ParseTree;


/// Malloc and return an empty ParseTree with a refCount of 1
ParseTree* parsetree_create (Token* token, int numChildren);

/// Increase a ParseTree's refCount by 1
void parsetree_reserve (ParseTree* tree);

/// Decrease a ParseTree's refCount by 1, and free it if refCount hits 0
void parsetree_release (ParseTree* tree);

/// Recursively print an entire ParseTree for debugging purposes
void parsetree_print (ParseTree * tree);


#endif