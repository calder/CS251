#ifndef PARSER_H
#define PARSER_H

#include "Parser/ParseTree.h"
#include "Util/Quack.h"


/// Return a complete ParseTree or NULL if a syntax error is encountered
/// @note The token list MUST have matched parentheses.
/// @note The token list is disassembled and freed by this operation.
ParseTree* parse (Quack* tokens);


#endif