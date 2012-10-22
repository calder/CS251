#ifndef PARSER_H
#define PARSER_H

#include "Parser/ParseTree.h"
#include "Util/Quack.h"


/// Given a Quack of tokens in which parenthesis are guaranteed to match,
/// returns a properly formed ParseTree.
ParseTree* parse (Quack* tokens);


#endif