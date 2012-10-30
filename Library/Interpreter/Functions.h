#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Interpreter/Value.h"


Value* function_lambda_eval (Closure* closure, ParseTree* args);


#endif