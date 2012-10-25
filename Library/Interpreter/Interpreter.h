#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Interpreter/Environment.h"
#include "Interpreter/SExpression.h"
#include "Parser/ParseTree.h"


/// Return the result of recursively turning a ParseTree into a SExpression
/// @note The tree is left untouched by this operation.
SExpression* evaluate (ParseTree* parseTree, Environment* environment);


#endif