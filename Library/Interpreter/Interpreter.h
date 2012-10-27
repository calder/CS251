#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Interpreter/Environment.h"
#include "Interpreter/Value.h"
#include "Parser/ParseTree.h"


/// Return the result of recursively turning a ParseTree into a Value
/// @note The original parseTree is completely freed in the process.
/// @note The returned Value* has a refCount of 1.
Value* evaluate (ParseTree* parseTree, Environment* environment);


#endif