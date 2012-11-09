#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Interpreter/Environment.h"
#include "Parser/ParseTree.h"
#include "Tokenizer/Value.h"
#include "Util/Quack.h"


/// Return a list of Values parsed and evaluated from the given input
Quack* interpret (const char* input);

/// Return the result of recursively turning a ParseTree into a Value
/// @note The original parseTree is left untouched, the parts of it may be used
/// by lambda expressions.  Since ParseTrees are reference counted though, you
/// may safely call parsetree_release() on the entire tree afterwords.
/// @note The returned Value* has a refCount of 1.
Value* evaluate (ParseTree* parseTree, Environment* environment);

/// Evaluate children 2 through N, and return the value of the final child
/// @note The environment is assumed to be a temporary and will be released by
/// this function.
Value* evaluate_bodies (ParseTree* parseTree, Environment* environment);

/// Return the result of recursively evaluating a list literal
/// @note This function is exactly like evaluate() with two exceptions:
///   - Subtrees are treated as lists instead of function calls.
///   - Symbols are kept as symbols rather than being evaluated.
Value* evaluate_list (ParseTree* parseTree);

/// Interpret a file in the given environment
/// @note This function is used by both the "load" keyword and for built-in 
/// library loading during interpreter startup.
bool load_file (Environment* environment, const char* filename);


#endif