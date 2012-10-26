#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Interpreter/Environment.h"
#include "Interpreter/Value.h"
#include "Parser/ParseTree.h"


/// Return the result of recursively turning a ParseTree into a Value
/// @note The tree is left untouched by this operation.
Value* evaluate (ParseTree* parseTree, Environment* environment);


#endif