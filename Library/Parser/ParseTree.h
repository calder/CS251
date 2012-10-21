#ifndef PARSETREE_H
#define PARSETREE_H


/// A parse tree (or subtree)
struct __ParseTree
{
	Token* token;
    __ParseTree** children;
    int numChildren;
}
typedef ParseTreeNode;


ParseTree* parsetree_create (Token* token, int numChildren);
void parsetree_free (ParseTree* tree);


#endif