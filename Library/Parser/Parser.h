#ifndef PARSER_H
#define PARSER_H

#include "Parser/ParseTree.h"
#include "Util/Quack.h"


/// Return a complete ParseTree or NULL if syntax error
/// @note The token list MUST have matched parentheses.
ParseTree* parse (Quack* tokens);


#endif