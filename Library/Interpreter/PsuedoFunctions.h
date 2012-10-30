#ifndef PSUEDO_FUNCTIONS_H
#define PSUEDO_FUNCTIONS_H

#include "Interpreter/Environment.h"


Value* function_if (Environment* environment, ParseTree* args);
Value* function_let (Environment* environment, ParseTree* args);
Value* function_lambda (Environment* environment, ParseTree* args);
Value* function_quote (Environment* environment, ParseTree* args);


#endif