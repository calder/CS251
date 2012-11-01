#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Interpreter/Environment.h"
#include "Parser/ParseTree.h"


Value* function_if (Environment* environment, ParseTree* args);
Value* function_let (Environment* environment, ParseTree* args);
Value* function_lambda (Environment* environment, ParseTree* args);
Value* function_quote (Environment* environment, ParseTree* args);


#endif