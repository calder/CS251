#include <stdlib.h>


ParseTreeNode* parsetreenode_create()
{
	ParseTreeNode* toReturn = malloc(sizeof(ParseTreeNode));
	toReturn->data = NULL;
	toReturn->children = NULL;
	toReturn->size = 0;
	return toReturn;
}