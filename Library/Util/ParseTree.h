#ifndef TREE_H
#define TREE_H

#include <stdbool.h>


/// As struct representation of a node in a parse tree
struct __ParseTreeNode 
{
	void* data;
	void **children;
	int numchildren;
}
typedef ParseTreeNode;

ParseTreeNode* parsetreenode_create();

#endif