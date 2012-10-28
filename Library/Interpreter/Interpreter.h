#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Interpreter/Environment.h"
#include "Interpreter/Value.h"
#include "Parser/ParseTree.h"
#include "Util/Quack.h"


/// Return a list of Values parsed and evaluated from the given input
Quack* interpret (const char* input);

/// Return the result of recursively turning a ParseTree into a Value
/// @note The original parseTree is left untouched, the parts of it may be used
/// by lambda expressions.  Since ParseTrees are reference counted though, you
/// may safely call parsetree_release() on the entire tree afterwords.
/// @note The returned Value* has a refCount of 1.
Value* evaluate (ParseTree* parseTree, Environment* environment);


#endif