#ifndef PARSER_H
#define PARSER_H

#include "Parser/ParseTree.h"
#include "Util/Quack.h"


/// Parse the string input into a ParseTree for each top-level expressions
/// @note parse() returns NULL if it encounters a syntax error or reaches the
/// end of input part way through an expression.
Quack* parse (char* input);

/// Read another line, parsing and appending any full expressions encountered
/// @return true iff no syntax errors were encountered.
bool parse_partial (const char* line, Quack* parens, Quack* tokens, Quack* expressions);

/// Return a complete ParseTree or NULL if a syntax error occured
/// @note The token list MUST be a single expression with matched parentheses.
/// @note The token list is emptied (but NOT freed) by this operation.
ParseTree* parse_expression (Quack* tokens);


#endif